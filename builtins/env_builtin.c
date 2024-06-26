/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:16:32 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/19 19:12:01 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_builtin(t_commands *cmd)
{
	t_env	*tmp;

	if (cmd->cmd_args[1])
		return (error_msg("env", "too many argumemts", EXIT_FAILURE));
	if (!cmd->env)
		return (EXIT_FAILURE);
	tmp = cmd->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
