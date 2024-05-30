/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:04:09 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/30 17:19:32 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is what the child process does.
 * First it closes the unused pipe file descriptors.
 * Then it retrieves the command to be executed based on the index of the command.
 * Then it duplicates the pipe file descriptors.
 * Then it checks for in/output redirection and duplicates the file descriptors.
 * Then it executes the command.
 */
static int	run_multichild(t_minishell *minishell, char **env)
{
	int				status;
	t_commands		*cmd;

	status = 0;
	cmd = minishell->commands;
	close_pipe_fd(minishell);
	while (minishell->index_cmd != cmd->index)
		cmd = cmd->next;
	dup_pipefd(minishell, cmd);
	if (dup_in_redir(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (dup_out_redir(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (execve(cmd->cmd_args[0], cmd->cmd_args, env) == -1)
	{
		perror(cmd->cmd_args[0]);
		free_shell(minishell);
		return (EXIT_FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief This function forks and executes the commands.
 * The parent forks and waits for the child to finish and then it forks again.
 * There will be only one parent process and multiple child processes, which will run
 * after each other.
 */
static int	fork_and_exec(t_minishell *minishell, char **env)
{
	int	i;
	int	status;

	i = 0;
	while (i < nb_cmd)
	{
		minishell->pid = fork();
		if (minishell->pid == -1)
		{
			perror("Fork");
			free_shell(minishell);
			return (EXIT_FAILURE);
		}
		if (minishell->pid == 0)
		{
			if (run_multichild(minishell, env) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
		{
			i++;
			wait(minishell->pid, &status, 0);
		}
	}
	return (status);
}
 /**
  * @brief This function creates the pipe_fd array in the minishell struct.
  */
static int	fill_pipefd(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->pipe_fd[i])
	{
		if (pipe(minishell->pipe_fd[i]) == -1)
		{
			perror("pipe");
			free_shell(minishell);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief This function creates the pipe_fd array in the minishell struct.
 * Then it fills the pipe_fd array with the pipe file descriptors.
 * Then executes the commands.
 */
static int	execute_cmds(t_minishell *minishell, char **env)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (create_pipe_fd(minishell, minishell->nb_cmd) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	if (fill_pipefd(minishell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	status = fork_and_exec(minishell, env);
	if (status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (status);
}

/**
 * @brief This function executes the commands in the minishell struct.
 * It counts the number of the commands, then transforms the env struct to a double array,
 * then if executes the commands.
 */
int	executor(t_minishell *minishell)
{
	int		i;
	int		status;
	char	**env;

	minishell->nb_cmd = count_cmds(minishell->commands);
	env = env_double(minishell->env);
	if (env == NULL)
	{
		free_shell(minishell);
		return (ALLOC_ERROR);
	}
	if (minishell->nb_cmd == 1)
	{
		minishell->exit_status = execute_simple_cmd(minishell, env);
		return (minishell->exit_status);
	}
	else
	{
		minishell->exit_status = execute_cmds(minishell, env);
		return (minishell->exit_status);
	}
	minishell->index_cmd = -1;
	close_pipe_fd(minishell);
	return (SUCCESS);
}
