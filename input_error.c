/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:22:20 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/29 23:11:44 by codespace        ###   ########.fr       */
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
				return (error);
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

int	error_check(char *input)
{
	if (quotes_check(input) == 1)
	{
		free (input);
		printf("Error: Unclosed quotes are not interpreted !!\n");
		return (1);
	}
	else if (semicolon(input) == 1)
	{
		free (input);
		printf("Error: Semicolons are not interpreted !!\n");
		return (1);
	}
	return (0);
}
