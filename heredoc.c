/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:52:08 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/21 19:04:33 by szerzeri         ###   ########.fr       */
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

/**
 * @brief This function reads the prompt from the user
 * @param eof the end of file token
 */
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

/**
 * @brief This function reads the heredoc from the user
 * and joins the lines together while adding a newline between each line
 * @param command the command that contains the heredoc
 * @param eof the end of file token
 */
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
			tmp->heredoc = read_heredoc(tmp, token->next->token);
			if (tmp->heredoc == NULL)
				return (ALLOC_ERROR);
			token = find_token(token->next, HEREDOC);
		}
		tmp = tmp->next;
	}
	return (0);
}
