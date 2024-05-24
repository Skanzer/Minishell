/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:04:09 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/24 19:22:26 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_commands *commands)
{
	t_commands	*tmp;
	int			len;

	tmp = commands;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	free_pipe(int **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	create_pipe_fd(t_minishell *minishell, int nb_cmd)
{
	int	i;

	i = 0;
	minishell->pipe_fd = ft_calloc(nb_cmd, sizeof(int *));
	if (!minishell->pipe_fd)
		return (ALLOC_ERROR);
	while (i < nb_cmd)
	{
		if (i == nb_cmd - 1)
			pipe_fd[i++] = NULL;
		else
		{
			pipe_fd[i++] = ft_calloc(2, sizeof(int));
			if (!pipe_fd[i])
			{
				free_pipe(minishell->pipe_fd);
				return (ALLOC_ERROR);
			}
		}
	}
	return (SUCCESS);
}

int	execute_simple_cmd(t_minishell *minishell)
{
	int	status;

	status = 0;
	minishell->pid = fork();
	if (minishell->pid == -1)
	{
		perror("fork");
		free_shell(minishell);
		exit(EXIT_FAILURE);
	}
	if (minishell->pid == 0)
	{
		if (execve(minishell->commands->cmd_args[0], minishell->commands->cmd_args, minishell->env) == -1)
		{
			perror("execve");
			free_mini(minishell);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(minishell->pid, &status, 0);
		minishell->exit_status = WEXITSTATUS(status);
	}
	return (status);
}

int	executor(t_minishell *minishell)
{
	int		nb_cmd;
	int		i;

	i = 0;
	nb_cmd = count_cmds(minishell->commands);
	if (nb_cmd == 1)
	{
		execute_simple_cmd(minishell);
		return (SUCCESS);
	}
	if (create_pipe_fd(minishell, nb_cmd) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	while (minishell->pipe_fd[i])
	{
		if (pipe(minishell->pipe_fd[i]) == -1)
		{
			perror("pipe");
			free_mini(minishell);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}