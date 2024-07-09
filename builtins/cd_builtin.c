/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:41:36 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/04 13:21:00 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_wd(t_minishell *mini, char *wd)
{
	char	**tmp;

	tmp = ft_calloc(3, sizeof(char *));
	tmp[0] = ft_strdup("OLDPWD");
	tmp[1] = ft_strdup(mini->pwd);
	tmp[2] = NULL;
	set_env_var(tmp, mini->env);
	free(tmp[0]);
	free(tmp[1]);
	tmp[0] = ft_strdup("PWD");
	tmp[1] = ft_strdup(wd);
	set_env_var(tmp, mini->env);
	free_double(tmp);
	if (mini->old_pwd)
	{
		free(mini->old_pwd);
		mini->old_pwd = ft_strdup(mini->pwd);
	}
	if (mini->pwd)
	{
		free(mini->pwd);
		mini->pwd = ft_strdup(wd);
	}
}

static int	chdir_errno_mod(void)
{
	if (errno == ESTALE)
		errno = ENOENT;
	error_msg("cd", strerror(errno), errno);
	return (0);
}

static int	change_dir(t_minishell *mini, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod());
	ret = getcwd(cwd, PATH_MAX);
	if(!ret)
	{
		error_msg("cd", "error retrieving current directory", errno);
		ret = ft_strjoin(mini->pwd, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free(tmp);
	}
	else
		ret = ft_strdup(cwd);
	update_wd(mini, ret);
	return (SUCCESS);
}

int	cd_builtin(t_minishell *mini, t_commands *cmd)
{
	char	*path;
	char	**args;

	args = cmd->cmd_args;
	if (!args[1] || space_char(args[1][0]) == 1 
			|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_var_value("HOME", mini->env);
		if (!path)
			return (error_msg("cd", "HOME not set", EXIT_FAILURE));
		return (change_dir(mini, path));
	}
	if (args[2])
		return (error_msg("cd", "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_var_value("OLDPWD", mini->env);
		if (!path)
			return (error_msg("cd", "OLDPWD not set", EXIT_FAILURE));
		return (change_dir(mini, path));
	}
	return (change_dir(mini, args[1]));
}
