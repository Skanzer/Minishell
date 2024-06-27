/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:19:59 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/27 14:36:26 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_builtin(t_minishell *mini)
{
	char	buf[PATH_MAX];
	char	*cwd;
	int		error;

	if (mini->pwd)
	{
		printf("%s\n", mini->pwd);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(buf, PATH_MAX);
	if (cwd)
	{
		printf("%s\n", cwd);
		return (EXIT_SUCCESS);
	}
	error = error_msg("pwd", NULL, errno);
	return (error);
}
