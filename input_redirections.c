/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:38:40 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/21 15:38:59 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input_redir(char *input_redir)
{
	if (access(input_redir, F_OK | R_OK) == -1)
	{
		perror(input_redir);
		return (1);
	}
	return (0);
}

int	input_redir(t_commands *commands)
{
	t_tokens	*token;
	t_commands	*tmp;

	tmp = commands;
	while (tmp)
	{
		token = find_token(tmp->tokens, REDIR_IN);
		while (token)
		{
			if (tmp->infile)
				free(tmp->infile);
			if (check_input_redir(token->next->token) == 1)
				return (1);
			tmp->infile = ft_strdup(token->next->token);
			if (tmp->infile == NULL)
				return (ALLOC_ERROR);
			token = find_token(token->next, REDIR_IN);
		}
		tmp = tmp->next;
	}
	return (0);
}
