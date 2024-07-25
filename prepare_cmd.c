/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:08:21 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/24 15:42:02 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function counts the number of tokens in the tokens linked list.
*/
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

/**
 * @brief This function puts the remaining tokens in a double pointer.
 * If this part is reached, it means that the tokens will only have the
 * command name and the arguments.
 */
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

/**
 * @brief This function goes through the environment linked list 
 * and returns the value of the environment variable.
 * @param env The environment linked list.
 * @param name The name of the environment variable.
*/
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

/**
 * @brief This function creates the command path 
 * by joining the path from the PATH
 * environment variable with the command name.
 * If the command name contains a '/', it returns the command name.
 * @param command The command linked list.
 * @param cmd The command name.
 * @return char* Returns the command path.
 */
char	*join_path(t_commands *command, char *cmd)
{
	char	*path;
	char	*tmp;
	char	**env_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	env_path = ft_split(get_from_env(command->env, "PATH"), ':');
	if (!env_path)
		return (ft_strdup(cmd));
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
	return (ft_strdup(cmd));
}

/**
 * @brief This function creates the command path 
 * and the command arguments.
 * it goes through the commands linked list and creates the command path
 * and the command arguments for each command.
 * @param commands The commands linked list.
 * @return int Returns 0 if the function was successful, 
 * 1 if there was an allocation error.
 */
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
		if (is_builtin(tmp->tokens->token) == 1)
			tmp->builtin = 1;
		else
		{
			tmp->cmd_path = join_path(tmp, tmp->tokens->token);
			if (!tmp->cmd_path)
				return (ALLOC_ERROR);
		}
		tmp->cmd_args = put_in_dbl(tmp->tokens);
		if (tmp->cmd_args == NULL)
			return (ALLOC_ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
