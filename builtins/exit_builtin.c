/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:50:12 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/17 16:57:57 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	get_code(char **args)
{
	int	i;

	i = 0;
	if (args[2] != NULL)
	{
		error_msg("exit", "too many arguments", 1);
		return (1);
	}
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			error_msg("exit", "numeric argument required", 2);
			return (2);
		}
		i++;
	}
	return (ft_atoi(args[1]));
}

int	exit_builtin(t_minishell *mini, t_commands *cmd)
{
	size_t	exit_code;

	if (mini->nb_cmd == 1)
		printf("exit\n");
	if (!cmd->cmd_args[1])
		exit_code = mini->exit_status;
	else
		exit_code = get_code(cmd->cmd_args);
	free_shell(mini);
	exit(exit_code);
}
