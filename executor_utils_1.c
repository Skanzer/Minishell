/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:45:57 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/23 15:16:37 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function checks if the command is executable or builtin
 * and executes the command.
 * Since the execve doensn't return the command not found error,
 * the function checks if the command is available or not.
 */
void	cmd_execution(t_minishell *mini, t_commands *command, char **env)
{
	int		ret;

	if (command->builtin == 1)
	{
		ret = execute_builtin(mini, command);
		free_double(env);
		exit (ret);
	}
	if (access(command->cmd_path, F_OK) == -1)
	{
		error_msg(command->cmd_args[0], "command not found", CMD_NOT_FOUND);
		free_double(env);
		exit(CMD_NOT_FOUND);
	}
	if (execve(command->cmd_path, command->cmd_args, env) == -1)
	{
		perror("Minishell");
		free_double(env);
		if (errno == 126)
			exit(CMD_NOT_EXECUTABLE);
		else
			exit(EXIT_FAILURE);
	}
}
