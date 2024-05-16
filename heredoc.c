/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:52:08 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/16 17:13:08 by szerzeri         ###   ########.fr       */
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

char	*process_line(t_commands *command, char *line)
{
	char	*tmp;

	if ((command->quoted_heredoc == 1))
	{
		if (input_expansion (line, command->env) == ALLOC_ERROR)
			return (NULL);
	}
	tmp = ft_strjoin(line, "\n");
	if (!tmp)
		return (NULL);
	free(line);
	return (tmp);
}

char	*read_prompt(char *eof)
{
	char	*line;

	line = readline("> ");
	if (!line)
		return (NULL);
	if (ft_strcmp(line, eof) == 0)
	{
		free(line);
		return ("");
	}
	return (line);
}

char	*read_heredoc(t_commands *command, char *eof)
{
	char	*line;
	char	*heredoc;
	char	*tmp;

	heredoc = ft_calloc(1, sizeof(char));
	if (!heredoc)
		return (NULL);
	while (1)
	{
		line = read_prompt(eof);
		if (!line)
			return (NULL);
		else if (ft_strcmp(line, "") == 0)
			break ;
		line = process_line(command, line);
		if (!line)
			return (NULL);
		tmp = heredoc;
		heredoc = ft_strjoin(heredoc, line);
		if (!heredoc)
			return (NULL);
		free(tmp);
		free(line);
	}
	return (heredoc);
}

int	heredoc(t_commands *commands)
{
	t_tokens	*token;
	t_commands	*tmp;

	tmp = commands;
	while (tmp)
	{
		token = heredoc_token(tmp->tokens);
		while (token)
		{
			if (tmp->heredoc)
				free(tmp->heredoc);
			tmp->heredoc = read_heredoc(tmp, token->next->token);
			if (tmp->heredoc == NULL)
				return (1);
			token = heredoc_token(token->next);
		}
		delete_token_node(tmp->tokens, HEREDOC);
		tmp = tmp->next;
	}
	return (0);
}
