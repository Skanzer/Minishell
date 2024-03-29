/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:29:05 by szerzeri          #+#    #+#             */
/*   Updated: 2024/02/08 14:22:19 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes(char *input, int i)
{
	int	copy;

	copy = i;
	while (input[i])
	{
		if (input[i] == '\'')
			return (i);
		else
			i++;
	}
	while (input[copy])
	{
		if (input[copy] == '"')
			return (copy);
		else
			copy++;
	}
	return (-1);
}

void	free_double(char **array, int i)
{
	if (!array)
		return;
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}
