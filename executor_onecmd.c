/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_onecmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:20:12 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/27 15:18:01 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_minishell *mini, t_commands *cmd)
{
	if (ft_strcmp(cmd->cmd_args[0], "cd") == 0)
		return (cd_builtin(mini, cmd));
	else if (ft_strcmp(cmd->cmd_args[0], "echo") == 0)
		return (echo_builtin(cmd));
	else if (ft_strcmp(cmd->cmd_args[0], "env") == 0)
		return (env_builtin(cmd));
	else if (ft_strcmp(cmd->cmd_args[0], "export") == 0)
		return (export_builtin(cmd));
	else if (ft_strcmp(cmd->cmd_args[0], "pwd") == 0)
		return (pwd_builtin(mini));
	else if (ft_strcmp(cmd->cmd_args[0], "unset") == 0)
		return (unset_builtin(mini));
	/*else if (ft_strcmp(cmd->cmd_args[0], "exit") == 0)
		return (exit_builtin(mini));*/
	return (0);
}

int	execute_one_cmd(t_minishell *minishell, char **env)
{
	int		status;

	status = 0;
	if (minishell->commands->cmd_args == NULL)
	{
		free_double(env);
		return (SUCCESS);
	}
	if (minishell->commands->builtin == 1)
	{
		status = execute_builtin(minishell, minishell->commands);
		free_double(env);
	}
	else
		status = fork_onecmd(minishell, env);
	return (status);
}
