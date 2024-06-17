/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:43:04 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/14 23:36:55 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	flag;
	int	i;
	char	**args;

	args = cmd->builtin;
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
		if (args[i++])
			printf(" ");
	}
	if (flag != 1)
		printf("\n");
	return (SUCCESS);
}
