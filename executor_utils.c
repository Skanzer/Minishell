/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:08:00 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/29 18:04:41 by szerzeri         ###   ########.fr       */
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
		tmp->index = len;
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

int	create_pipe_fd(t_minishell *minishell)
{
	int				i;
	t_minishell		*tmp;

	i = 0;
	tmp = minishell;
	minishell->pipe_fd = ft_calloc(tmp->nb_cmd, sizeof(int *));
	if (!minishell->pipe_fd)
		return (ALLOC_ERROR);
	while (i < tmp->nb_cmd)
	{
		if (i == tmp->nb_cmd - 1)
			minishell->pipe_fd[i++] = NULL;
		else
		{
			minishell->pipe_fd[i++] = ft_calloc(2, sizeof(int));
			if (!minishell->pipe_fd[i])
			{
				free_pipe(minishell->pipe_fd);
				return (ALLOC_ERROR);
			}
		}
	}
	return (SUCCESS);
}

void	close_pipe_fd(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->nb_cmd - 1)
	{
		if (i != minishell->index_cmd - 1)
			close(minishell->pipe_fd[i][0]);
		if (i != minishell->index_cmd)
			close(minishell->pipe_fd[i][1]);
		i++;
	}
}
