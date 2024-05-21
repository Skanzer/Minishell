/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:48:35 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/21 18:51:22 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	output_redir(t_commands *commands)
{
	t_tokens	*token;
	t_commands	*tmp;
	int			fd;

	tmp = commands;
	while (tmp)
	{
		token = find_token(tmp->tokens, REDIR_OUT);
		while (token)
		{
			if (tmp->outfile)
				free(tmp->outfile);
			tmp->outfile = ft_strdup(token->next->token);
			fd = open_file(tmp->outfile, 1);
			if (fd == -1)
				return (1);
			close(fd);
			token = find_token(token->next, REDIR_OUT);
		}
		tmp = tmp->next;
	}
	return (0);
}