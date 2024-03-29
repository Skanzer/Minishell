/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:45:31 by szerzeri          #+#    #+#             */
/*   Updated: 2024/02/14 16:59:40 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_sign(char *input, int index)
{
	int	i;

	i = index;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'')
				i++;
		}
		if (input[i] == '$')
			return (i);
		else
			i++;
	}
	return (0);
}

char	*var_name(char *input, int index)
{
	char	*var;
	int		count;
	int		i;

	i = index + 1;
	count = 0;
	while (input[i] != '\0' && input[i] != ' ' && input[i] != '"')
	{
		i++;
		count++;
	}
	var = malloc(sizeof(char) * count + 1);
	if (!var)
		return (NULL);
	printf("count = %i\n", count);
	ft_strlcpy(var, &input[index + 1], count + 1);
	return (var);
}

char	*input_expansion(char *input)
{
	//char	*expanded;
	char	*var;
	char	*var_value;
	int		i;

	i = dollar_sign(input, 0);
	if (i != 0)
	{
		var = var_name(input, i);
		var_value = getenv(var);
		printf("variable = %s\n", var);
		printf("variable = %s\n", var_value);
	}
	return (NULL);

}
