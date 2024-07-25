/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_onecmd_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:58:21 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/24 16:48:37 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function checks if the file is readble and opens it for reading
 * and puts the file descriptor in the infile_fd variable
 */
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

/**
 * @brief This function preps the output redirection
 * if it's an outfile it opens the file for writing
 * if it's an append it opens the file for appending
 * and puts the file descriptor in the outfile_fd variable
 */
int	prep_out_redir(t_minishell *minishell)
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

/**
 * @brief This function preps the input redirection
 * if it's an infile it calls the infile_fd function
 * and if it's a heredoc it creates a pipe and writes the heredoc to the pipe
 */
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

/**
 * @brief This function sets the right in- and output redirections
 * and then executes the command 
 * @param minishell The minishell structure
 * @param env The environment variables in a double array format
 */
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
	cmd_execution(minishell, minishell->commands, env);
	return (SUCCESS);
}

/**
 * @brief When a command is executable and not a builtin, this function is used
 * it forks and executes the command
 * @param minishell The minishell structure
 * @param env The environment variables in a double array format
 */
int	fork_onecmd(t_minishell *minishell, char **env)
{
	int	status;

	status = 0;
	minishell->pid = fork();
	if (minishell->pid == -1)
	{
		perror("Fork");
		return (EXIT_FAILURE);
	}
	if (minishell->pid == 0)
	{
		if (run_onechild(minishell, env) == EXIT_FAILURE)
			status = EXIT_FAILURE;
	}
	else
		waitpid(minishell->pid, &status, 0);
	return (status);
}
