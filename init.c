/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:49:38 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/19 15:51:29 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_memory(t_minishell *minishell)
{
	minishell->input = NULL;
	minishell->commands = NULL;
	minishell->pipe_fd = NULL;
	minishell->exit_status = 0;
	minishell->pid = -1;
	minishell->index_cmd = 0;
	minishell->nb_cmd = 0;
	minishell->old_pwd = get_var_value("OLDPWD", minishell->env);
	minishell->pwd = get_var_value("PWD", minishell->env);
	return (0);
}

int	init_shell(t_minishell *minishell, char **env, int argc, char **argv)
{
	if (argc != 1)
	{
		printf("argv[0]: %s is the only argument needed to run minishell\n", \
		argv[0]);
		return (1);
	}
	minishell->env = ft_calloc(1, sizeof(t_env));
	if (!minishell->env)
		return (ALLOC_ERROR);
	if (get_env(minishell, env) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	if (init_memory(minishell) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	if (!minishell->env)
		return (ALLOC_ERROR);
	return (0);
}
