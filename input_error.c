/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:22:20 by szerzeri          #+#    #+#             */
/*   Updated: 2024/02/13 18:43:59 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes_check(const char *input)
{
	int		i;
	int		error;
	char	q;

	i = 0;
	error = 1;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			q = input[i];
			i++;
			while (input[i] && input[i] != q)
				i++;
			if (input[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	semicolon(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

void	error_check(char *input)
{
	if (quotes_check(input) == 1)
	{
		free (input);
		printf("Error: Unclosed quotes are not interpreted !!\n");
	}
	else if (semicolon(input) == 1)
	{
		free (input);
		printf("Error: Semicolons are not interpreted !!\n");
	}
}