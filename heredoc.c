/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:52:08 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/17 19:53:22 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function processes the line
 * it adds the newline between the line and the next one
 * and checks if the line is quoted
 * if it's quoted, it expands the variables inside of the line
 * @param command the command that contains the heredoc
 * @param line the line to process
 */
static char	*process_line(t_commands *cmd, char *line)
{
	char	*tmp;

	if (cmd->quoted_heredoc != 1)
	{
		line = input_expansion(line, cmd->env, cmd->exit_status);
		if (line == NULL)
			return (NULL);
	}
	tmp = ft_strjoin(line, "\n");
	if (!tmp)
		return (NULL);
	free(line);
	return (tmp);
}

/**
 * @brief This function reads the prompt from the user
 * @param eof the end of file token
 */
static char	*read_prompt(char *eof)
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

/**
 * @brief This function reads the heredoc from the user
 * and joins the lines together while adding a newline between each line
 * @param command the command that contains the heredoc
 * @param eof the end of file token
 */
static char	*read_heredoc(t_commands *command, char *eof)
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
		if (!line || g_interrupt == 1)
			return (free(heredoc), NULL);
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

/**
 * @brief This function go through the commands
 * and check if there is a heredoc token
 * if it's the case, it gives the user a prompt
 * to write the heredoc and store it in the heredoc variable
 */
int	heredoc(t_commands *commands)
{
	t_tokens	*token;
	t_commands	*tmp;

	tmp = commands;
	while (tmp)
	{
		token = find_token(tmp->tokens, HEREDOC);
		while (token)
		{
			if (tmp->heredoc)
				free(tmp->heredoc);
			sig_handler();
			tmp->heredoc = read_heredoc(tmp, token->next->token);
			if (g_interrupt == 1)
				break ;
			if (tmp->heredoc == NULL)
				return (ALLOC_ERROR);
			token = find_token(token->next, HEREDOC);
		}
		tmp = tmp->next;
	}
	return (0);
}
