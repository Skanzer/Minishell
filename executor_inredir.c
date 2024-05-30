/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_inredir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:16:09 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/30 17:09:40 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function checks if the command has in input redirection and
 * opens the file to read the input of the command.
 * It closes the Read end of the pipe if the command is not the first
 * and closes the STDIN if it is the first command.
 */
int	dup_infile(t_minishell *minishell, t_commands *cmd)
{
	if (cmd->infile)
	{
		cmd->infile_fd = open(cmd->infile, O_RDONLY);
		if (cmd->infile_fd == -1)
		{
			perror(cmd->infile);
			free_shell(minishell);
			return (EXIT_FAILURE);
		}
		if (cmd->index != 0)
		{
			dup2(cmd->infile_fd, minishell->pipe_fd[cmd->index - 1][READ]);
			close(cmd->infile_fd);
		}
		else
		{
			dup2(cmd->infile_fd, STDIN_FILENO);
			close(cmd->infile_fd);
		}
	}
	return (SUCCESS);
}

/**
 * @brief This function checks if the command has a heredoc and
 * open a new pipe to write the heredoc.
 * It closes the Read end of the pipe if the command is not the first
 * and closes the STDIN if it is the first command.
 * It then writes to the pipe the heredoc.
 */
int	dup_heredoc(t_minishell *minishell, t_commands *cmd)
{
	int	pipe_fd[2];

	if (cmd->heredoc)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			free_shell(minishell);
			return (EXIT_FAILURE);
		}octl, g
		if (cmd->index == 0)
		{
			dup2(pipe_fd[READ], STDIN_FILENO);
			close(pipe_fd[READ]);
		}
		else
		{
			dup2(pipe_fd[READ], minishell->pipe_fd[cmd->index - 1][READ]);
			close(pipe_fd[READ]);
		}
		write(pipe_fd[WRITE], cmd->heredoc, ft_strlen(cmd->heredoc));
		close(pipe_fd[WRITE]);
	}
	return (SUCCESS);
}

/**
 * @brief This function checks if the command has an input or output redirections
 * and calls the functions to handle them.
 */
int	dup_in_redir(t_minishell *minishell, t_commands *cmd)
{
	if (dup_infile(minishell, cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (dup_heredoc(minishell, cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (SUCCESS);
}
