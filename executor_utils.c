/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:08:00 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/22 20:51:53 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function counts the number of commands in the linked list.
 */
int	count_cmds(t_commands *commands)
{
	t_commands	*tmp;
	int			len;

	tmp = commands;
	len = 0;
	while (tmp)
	{
		tmp->index = len;
		len++;
		tmp = tmp->next;
	}
	return (len);
}

/**
 * @brief This function frees the double array storing 
 * the pipes file descriptors.
*/
void	free_pipe(t_minishell *mini, int **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < mini->nb_cmd - 1 && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/**
 * @brief This function creates the double array to store
 * the pipes file descriptors.
 */
int	**create_pipe_fd(t_minishell *minishell)
{
	int	i;
	int	**pipe_fd;

	i = 0;
	pipe_fd = (int **)ft_calloc(minishell->nb_cmd - 1, sizeof(int *));
	if (!pipe_fd)
		return (NULL);
	while (i < minishell->nb_cmd - 1)
	{
		pipe_fd[i] = (int *)ft_calloc(2, sizeof(int));
		if (!pipe_fd[i])
		{
			free_pipe(minishell, pipe_fd);
			return (NULL);
		}
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("pipe");
			free_pipe(minishell, pipe_fd);
			return (NULL);
		}
		i++;
	}
	return (pipe_fd);
}

/**
 * @brief This function closes the unused pipes file descriptors.
 */
void	close_pipe_fd(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->nb_cmd - 1)
	{
		if (i != minishell->index_cmd - 1)
			close(minishell->pipe_fd[i][READ]);
		if (i != minishell->index_cmd)
			close(minishell->pipe_fd[i][WRITE]);
		i++;
	}
}

/**
 * @brief This function duplicates the write and read end 
 * of the pipe to the stdout and stdin.
 * It closes the write end of the pipe if the command is not the last
 * and closes the read end of the pipe if it is the first command.
 */
void	dup_pipefd(t_minishell *minishell, t_commands *cmd)
{
	if (cmd->index != minishell->nb_cmd - 1)
	{
		dup2(minishell->pipe_fd[cmd->index][WRITE], STDOUT_FILENO);
		close(minishell->pipe_fd[cmd->index][WRITE]);
	}
	if (cmd->index != 0)
	{
		dup2(minishell->pipe_fd[cmd->index - 1][READ], STDIN_FILENO);
		close(minishell->pipe_fd[cmd->index - 1][READ]);
	}
}
