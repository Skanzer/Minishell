/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_onecmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:20:12 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/24 15:07:48 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function executes the builtin commands.
 * it compares the name of the command with the builtin commands
 * and executes them.
 */
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
	else if (ft_strcmp(cmd->cmd_args[0], "exit") == 0)
		return (exit_builtin(mini, cmd));
	return (0);
}

/**
 * @brief This function checks if the command is executable or builtin
 * @param minishell The minishell structure
 * @param env The environment variables ina double array format
 */
int	execute_one_cmd(t_minishell *minishell, char **env)
{
	int		status;
	int		test;

	status = 0;
	if (minishell->commands->cmd_args == NULL)
	{
		free_double(env);
		return (SUCCESS);
	}
	if (minishell->commands->builtin == 1)
	{
		test = dup(STDOUT_FILENO);
		prep_out_redir(minishell);
		status = execute_builtin(minishell, minishell->commands);
		if (minishell->commands->outfile_fd != -1)
		{
			dup2(test, STDOUT_FILENO);
			close(minishell->commands->outfile_fd);
		}
	}
	else
		status = fork_onecmd(minishell, env);
	return (status);
}
