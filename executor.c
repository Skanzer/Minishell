/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:04:09 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/29 18:54:26 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_mulitchild(t_minishell *minishell, char **env)
{
	int				status;
	t_commands		*tmp;

	status = 0;
	tmp = minishell->commands;
	close_pipe_fd(minishell);
	while (minishell->index_cmd != tmp->index)
		tmp = tmp->next;
	if ()
	
}

int	executor(t_minishell *minishell)
{
	int		i;
	int		status;
	char	**env;

	i = 0;
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
	if (create_pipe_fd(minishell, nb_cmd) == ALLOC_ERROR)
		return (ALLOC_ERROR);
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
	return (SUCCESS);
}
