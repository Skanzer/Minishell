/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:22:20 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/21 09:47:41 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**This function checks for unclosed quotes in the input
 */
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

/**This function checks for semicolons in the input
 */
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

/**This function checks if there is a pipe
 * in the beginning of the input and
 * if there are two consecutive pipes
 */
int	pipe_begin(char *input)
{
	int	i;

	i = 0;
	while (space_char(input[i]) == 1 && input[i])
		i++;
	if (input[i] == '|')
		return (1);
	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			while (space_char(input[i]) == 1 && input[i])
				i++;
			if (input[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

/**This function checks if the input is empty or not
 */
int	empty_input(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (1);
	while (input[i])
	{
		if (space_char(input[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

/**This function checks for syntax error in the input
 * it checks for unclosed quotes, semicolons,
 * pipes at the beginning of the input,
 * two consecutive pipes and empty input
 */
int	error_check(char *input)
{
	if (empty_input(input) == 1)
	{
		free (input);
		printf("\n");
		return (1);
	}
	else if (quotes_check(input) == 1)
	{
		free (input);
		printf("Minishell: Unclosed quotes are not interpreted !!\n");
		return (1);
	}
	else if (semicolon(input) == 1)
	{
		free (input);
		printf("Minishell: Semicolons are not interpreted !!\n");
		return (1);
	}
	else if (pipe_begin(input) == 1 || redirection_error(input) == 1)
	{
		free (input);
		printf("Minishell: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}
