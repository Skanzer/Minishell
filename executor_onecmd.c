/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_onecmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:20:12 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/04 16:22:17 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	infile_fd(t_minishell *minishell)
{
	minishell->commands->infile_fd = open(minishell->commands->infile, \
																O_RDONLY);
	if (minishell->commands->infile_fd == -1)
	{
		perror(minishell->commands->infile);
		return (EXIT_FAILURE);
	}
	dup2(minishell->commands->infile_fd, STDIN_FILENO);
	close(minishell->commands->infile_fd);
	return (SUCCESS);
}

static int	prep_out_redir(t_minishell *minishell)
{
	t_commands	*tmp;

	tmp = minishell->commands;
	if (tmp->outfile || tmp->append)
	{
		if (tmp->outfile)
			tmp->outfile_fd = open(tmp->outfile, \
								O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else
			tmp->outfile_fd = open(tmp->append, \
								O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (tmp->outfile_fd == -1)
		{
			perror(tmp->outfile);
			return (EXIT_FAILURE);
		}
		dup2(tmp->outfile_fd, STDOUT_FILENO);
		close(tmp->outfile_fd);
	}
	return (SUCCESS);
}

static int	prep_in_redir(t_minishell *minishell)
{
	int		pipe_fd[2];

	if (minishell->commands->infile)
	{
		if (infile_fd(minishell) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (minishell->commands->heredoc)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			free_shell(minishell);
			return (EXIT_FAILURE);
		}
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		write(pipe_fd[1], minishell->commands->heredoc, \
					ft_strlen(minishell->commands->heredoc));
		close(pipe_fd[1]);
	}
	return (SUCCESS);
}

static int	run_onechild(t_minishell *minishell, char **env)
{
	if (prep_in_redir(minishell) == EXIT_FAILURE)
	{
		free_shell(minishell);
		free_double(env);
		exit(EXIT_FAILURE);
	}
	if (prep_out_redir(minishell) == EXIT_FAILURE)
	{
		free_shell(minishell);
		free_double(env);
		exit(EXIT_FAILURE);
	}
	if (execve(minishell->commands->cmd_path, \
								minishell->commands->cmd_args, env) == -1)
	{
		error_msg(minishell->commands->cmd_args[0]);
		free_double(env);
		free_shell(minishell);
		if (errno == 127)
			exit(CMD_NOT_FOUND);
		else if (errno == 126)
			exit(CMD_NOT_EXECUTABLE);
		else
			exit(EXIT_FAILURE);
	}
	return (SUCCESS);
}

int	execute_simple_cmd(t_minishell *minishell, char **env)
{
	int		status;

	status = 0;
	if (minishell->commands->cmd_args == NULL)
	{
		free_double(env);
		return (SUCCESS);
	}
	minishell->pid = fork();
	if (minishell->pid == -1)
	{
		perror("Fork");
		return (EXIT_FAILURE);
	}
	if (minishell->pid == 0)
	{
		if (run_onechild(minishell, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		free_double(env);
		waitpid(minishell->pid, &status, 0);
	}
	return (status);
}
