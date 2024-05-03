/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:52:08 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/03 18:40:40 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*heredoc_token(t_tokens	*token)
{
	t_tokens	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	heredoc(t_commands *commands)
{
	char		*line;
	char		*eof;
	t_tokens	*token;
	t_commands	*tmp;

	tmp = commands;
	while (tmp)
	{
		token = heredoc_token(tmp->tokens);
		while (token)
		{
			 
		}
	}
	
}