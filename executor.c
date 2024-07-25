/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:04:09 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/24 15:09:10 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is what the child process does.
 * First it closes the unused pipe file descriptors.
 * Then it retrieves the command to be executed based
 * on the index of the command.
 * Then it duplicates the pipe file descriptors.
 * Then it checks for in/output redirection and duplicates the file descriptors.
 * Then it executes the command.
 */
static int	run_multichild(t_minishell *minishell, char **env)
{
	t_commands		*cmd;

	cmd = minishell->commands;
	close_pipe_fd(minishell);
	while (minishell->index_cmd != cmd->index)
		cmd = cmd->next;
	if (cmd->cmd_args == NULL)
	{
		free_double(env);
		free_shell(minishell);
		exit (SUCCESS);
	}
	dup_pipefd(minishell, cmd);
	if (dup_in_redir(minishell, cmd) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (dup_out_redir(minishell, cmd) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	cmd_execution(minishell, cmd, env);
	return (SUCCESS);
}

/**
 * @brief This function forks and executes the commands.
 * The parent forks and waits for the child to finish and then it forks again.
 * There will be only one parent process and multiple child processes,
 * which will run after each other.
 */
static int	fork_and_exec(t_minishell *minishell, char **env)
{
	int	i;
	int	status;

	i = 0;
	while (i < minishell->nb_cmd)
	{
		minishell->pid = fork();
		if (minishell->pid == -1)
		{
			free_double(env);
			free_shell(minishell);
			exit(EXIT_FAILURE);
		}
		if (minishell->pid == 0)
			run_multichild(minishell, env);
		else
		{
			if (i != minishell->nb_cmd - 1)
				close(minishell->pipe_fd[minishell->index_cmd][WRITE]);
			i++;
			minishell->index_cmd++;
			waitpid(-1, &status, 0);
		}
	}
	return (status);
}

/**
 * @brief This function creates the pipe_fd array in the minishell struct.
 * Then it fills the pipe_fd array with the pipe file descriptors.
 * Then executes the commands.
 */
static int	execute_cmds(t_minishell *minishell, char **env)
{
	int	status;

	status = 0;
	minishell->pipe_fd = create_pipe_fd(minishell);
	if (minishell->pipe_fd == NULL)
		return (EXIT_FAILURE);
	status = fork_and_exec(minishell, env);
	if (status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (status);
}

/**
 * @brief This function executes the commands in the minishell struct.
 * It counts the number of the commands,
 * then transforms the env struct to a double array,
 * then if executes the commands.
 */
int	executor(t_minishell *minishell)
{
	char	**env;

	minishell->nb_cmd = count_cmds(minishell->commands);
	env = env_double(minishell->env);
	if (env == NULL)
	{
		free_shell(minishell);
		exit(ALLOC_ERROR);
	}
	if (minishell->nb_cmd == 1)
	{
		minishell->exit_status = WEXITSTATUS(execute_one_cmd(minishell, env));
		free_double(env);
		return (minishell->exit_status);
	}
	else
	{
		minishell->exit_status = WEXITSTATUS(execute_cmds(minishell, env));
		free_double(env);
		return (minishell->exit_status);
	}
	return (SUCCESS);
}
