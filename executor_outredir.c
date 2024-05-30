/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_outredir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:07:30 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/30 17:05:50 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function checks if the command has an output redirection and
 * opens the file to write the output of the command.
 * It closes the Write end of the pipe if the command is not the last
 * and closes the STDOUT if it is the last command.
 */
int	dup_out_redir(t_minishell *minishell, t_commands *cmd)
{
	if (cmd->outfile || cmd->append)
	{
		if (cmd->outfile)
			cmd->outfile_fd = open(cmd->outfile, \
								O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else
			cmd->outfile_fd = open(cmd->append, \
								O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (cmd->outfile_fd == -1)
		{
			perror(cmd->outfile);
			return (EXIT_FAILURE);
		}
		if (cmd->index == minishell->nb_cmd - 1)
		{
			dup2(cmd->outfile_fd, STDOUT_FILENO);
			close(cmd->outfile_fd);
		}
		else
		{
			dup2(cmd->outfile_fd, minishell->pipe_fd[cmd->index][WRITE]);
			close(cmd->outfile_fd);
		}
	}
	return (SUCCESS);
}
