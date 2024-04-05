/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:29:05 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/05 15:51:44 by szerzeri         ###   ########.fr       */
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

unsigned int	ft_strcpy(char *dest, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	return (i);
}
