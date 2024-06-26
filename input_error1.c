/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:22:36 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/16 13:34:45 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_check(char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	while (space_char(input[i]) == 1)
		i--;
	if (input[i] == '>' || input[i] == '<')
		return (1);
	return (0);
}

/**
 * @brief This function checks if there is a redirection in the end of the input
 * @param input the input string
 * returns 1 if there is a redirection in the end of the input
 * returns 0 if there is no redirection in the end of the input
 */
int	redirection_error(char *input)
{
	char	**split;
	char	*c;
	int		i;

	i = 0;
	c = "|";
	split = ft_split_new(input, c);
	if (!split)
		return (ALLOC_ERROR);
	while (split[i])
	{
		if (redir_check(split[i]) == 1)
		{
			free_double(split);
			return (1);
		}
		i++;
	}
	free_double(split);
	return (SUCCESS);
}

/**@brief This function checks if there is a syntax
 * error (redirection), after tokenizing the input
 * @param commands the commands struct
 */
int	after_redir_check(t_commands *commands)
{
	t_commands	*tmp_c;
	t_tokens	*tmp_t;

	tmp_c = commands;
	while (tmp_c)
	{
		tmp_t = tmp_c->tokens;
		while (tmp_t)
		{
			if (tmp_t->type == REDIR_OUT || tmp_t->type == REDIR_IN \
				|| tmp_t->type == REDIR_APPEND || tmp_t->type == HEREDOC)
			{
				if (!tmp_t->next)
					return (1);
				if (tmp_t->next->type != WORD)
					return (1);
			}
			tmp_t = tmp_t->next;
		}
		tmp_c = tmp_c->next;
	}
	return (0);
}
