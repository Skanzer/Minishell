/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:45:31 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/16 17:18:53 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**This function gets the variable name from the input string
 * @param input the input string
 * @param i the index of the dollar sign
 * @return the variable name
 */
static char	*get_var_name(char *input, int i)
{
	char	*var_name;
	int		var_len;

	var_len = 0;
	i++;
	while (input[i])
	{
		if (end_var_name(input[i]) == 1)
			break ;
		var_len++;
		i++;
	}
	var_name = malloc(sizeof(char) * (var_len + 1));
	if (!var_name)
		return (NULL);
	i = i - var_len;
	var_len = 0;
	while (input[i])
	{
		if (end_var_name(input[i]) == 1)
			break ;
		var_name[var_len++] = input[i++];
	}
	var_name[var_len] = '\0';
	return (var_name);
}

/**This function deletes the var_name and the dollar sign
 * and resize the string
 * @param input the input string
 * @param i the index of the variable name
 * @param len the length of the variable name
 */
static char	*remove_var(char *input, int i, int len)
{
	char	*tmp;
	int		j;
	int		k;

	tmp = malloc(sizeof(char) * (ft_strlen(input) - len));
	if (!tmp)
		return (NULL);
	j = 0;
	k = 0;
	while (input[j])
	{
		if (j == i)
			j = j + len + 1;
		tmp[k] = input[j];
		j++;
		k++;
	}
	tmp[k] = '\0';
	free(input);
	return (tmp);
}

/**
 * @brief This function inserts the var value to the input string
 * or remove the var_name and the dollar sign if the var doesn't exist
 * @param input the input string
 * @param i the index of the variable name
 * @param env the environment variables
 */
char	*handle_expansion(char *input, int i, t_env *env)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;

	var_name = get_var_name(input, i);
	if (!var_name)
		return (NULL);
	var_value = get_var_value(var_name, env);
	if (!var_value)
	{
		tmp = remove_var(input, i, ft_strlen(var_name) + 1);
		free(var_name);
		free(var_value);
		if (!tmp)
			return (NULL);
	}
	else
	{
		tmp = insert_var(input, i, var_value, var_name);
		free(var_name);
		free(var_value);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

/**This function takes the input and expands the variables in it
 * by replacing the variable name with its value.
 * @param input the input string
 * @param env the environment variables
 */
int	input_expansion(char *input, t_env *env)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			skip_single_quotes(input, &i);
		else if (input[i] != '$')
			i++;
		else if (input[i] == '$' && end_var_name(input[i + 1]) == 1)
			i = i + 1;
		else if (input[i] == '$')
		{
			input = handle_expansion(input, i, env);
			if (!input)
				return (ALLOC_ERROR);
		}
	}
	return (SUCCESS);
}
