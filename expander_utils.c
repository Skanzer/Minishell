/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:08:03 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/01 15:09:34 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**This function skips the single quotes in the input string
 * @param input the input string
 * @param i the index of the single quote
 */
void skip_single_quotes(char *input, int *i)
{
	(*i)++;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	(*i)++;
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
	while (input[j])
	{
		if (j == i)
		{
			k = k + ft_strlen(name) + 1;
			while (*value)
				tmp[j++] = *value++;
		}
		tmp[j++] = input[k++];
	}
	tmp[j] = '\0';
	free(input);
	return (tmp);
}
