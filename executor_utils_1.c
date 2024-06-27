/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:45:57 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/19 19:02:01 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_execution(t_commands *command, char **env)
{
	if (access(command->cmd_path, F_OK | R_OK) == -1)
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
