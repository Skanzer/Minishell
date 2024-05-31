/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_input_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:06:58 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/31 21:45:02 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_pipe_end(char *input)
{
	int	len;

	len = ft_strlen(input) - 1;
	while (space_char(input[len]) == 1)
		len--;
	if (input[len] == '|')
		return (1);
	return (0);
}

int	join_input_pipe(char *input)
{
	char	*line;
	char	*tmp;

	if (empty_input(input) == 1)
		return (SUCCESS);
	while (if_pipe_end(input) == 1)
	{
		line = readline("> ");
		if (!line)
		{
			free(input);
			return (ALLOC_ERROR);
		}
		tmp = ft_strjoin(input, line);
		free(line);
		free(input);
		if (!tmp)
			return (ALLOC_ERROR);
		input = ft_strdup(tmp);
		free(tmp);
		if (!input)
			return (ALLOC_ERROR);
	}
	return (SUCCESS);
}
