/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:08:21 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/04 14:05:43 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;
	int			len;

	tmp = tokens;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**put_in_dbl(t_tokens *tokens)
{
	t_tokens	*tmp;
	int			len;
	char		**dbl;

	len = count_tokens(tokens);
	dbl = ft_calloc(len + 1, sizeof(char *));
	if (!dbl)
		return (NULL);
	tmp = tokens;
	len = 0;
	while (tmp)
	{
		dbl[len] = ft_strdup(tmp->token);
		if (!dbl[len])
		{
			free_double(dbl);
			return (NULL);
		}
		len++;
		dbl[len] = NULL;
		tmp = tmp->next;
	}
	return (dbl);
}

char	*get_from_env(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*join_path(t_commands *command, char *cmd)
{
	char	*path;
	char	*tmp;
	char	**env_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	env_path = ft_split(get_from_env(command->env, "PATH"), ':');
	if (!env_path)
		return (NULL);
	i = 0;
	while (env_path[i])
	{
		tmp = ft_strjoin(env_path[i++], "/");
		path = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(path, F_OK | R_OK) == 0)
		{
			free_double(env_path);
			return (path);
		}
		free (path);
	}
	free_double(env_path);
	return (cmd);
}

int	create_cmd_args(t_commands *commands)
{
	t_commands	*tmp;

	tmp = commands;
	while (tmp)
	{
		if (!tmp->tokens)
		{
			tmp = tmp->next;
			continue ;
		}
		tmp->cmd_path = join_path(tmp, tmp->tokens->token);
		if (!tmp->cmd_path)
			return (ALLOC_ERROR);
		tmp->cmd_args = put_in_dbl(tmp->tokens);
		if (tmp->cmd_args == NULL)
			return (ALLOC_ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
