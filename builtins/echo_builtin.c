/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:43:04 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/28 17:39:37 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	nflag_check(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '-')
		return (0);
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

int	echo_builtin(t_commands *cmd)
{
	int		flag;
	int		i;
	char	**args;

	args = cmd->cmd_args;
	if (!args[1])
	{
		printf("\n");
		return (SUCCESS);
	}
	i = 1;
	flag = 0;
	if (nflag_check(args[1]) == 1)
		flag = i++;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[++i])
			printf(" ");
	}
	if (flag != 1)
		printf("\n");
	return (SUCCESS);
}
