/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:08:03 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/23 12:35:01 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**This function skips the single quotes in the input string
 * @param input the input string
 * @param i the index of the single quote
 */
void	skip_single_quotes(char *input, int *i)
{
	(*i)++;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	(*i)++;
}

static void	insert_var_fix(char *input, char *tmp, int j)
{
	tmp[j] = '\0';
	free(input);
}

/**This function inserts the var value to the string
 * @param input the input string
 * @param i the index of the variable name
 * @param value the value of the variable
 * @param name the name of the variable
 * @return the new string with the variable value inserted
*/
char	*insert_var(char *input, int i, char *value, char *name)
{
	char	*tmp;
	int		len;
	int		j;
	int		k;

	j = 0;
	k = 0;
	len = ft_strlen(input) + ft_strlen(value) - (ft_strlen(name) + 1);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	while (input[k])
	{
		if (j == i)
		{
			k = k + ft_strlen(name) + 1;
			while (*value)
				tmp[j++] = *value++;
		}
		if (input[k] == '\0')
			break ;
		tmp[j++] = input[k++];
	}
	insert_var_fix(input, tmp, j);
	return (tmp);
}

/**This function gets the value of the variable
 * @param var the name of the variable
 * @param env the environment variables
 * @return the value of the variable
 */
char	*get_var_value(char *var, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->name) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
