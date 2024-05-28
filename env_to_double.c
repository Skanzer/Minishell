/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:51:16 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/28 16:45:36 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function return the size of the env linked list
 */
static int	size_env(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

/**
 * @brief This function join the name and value of the env linked list
 * with a "=" between them
 */
static char	*join_name_value(t_env *env)
{
	char	*tmp;
	char	*envp;

	tmp = ft_strjoin(env->name, "=");
	if (!tmp)
		return (NULL);
	envp = ft_strjoin(tmp, env->value);
	free(tmp);
	if (!envp)
		return (NULL);
	return (envp);
}

/**
 * @brief Convert the env linked list to a double pointer
 * join the name and value of the env linked list
 * the double pointer is used by execve
 * @param env the env linked list
 */
char	**env_double(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		size;
	int		i;

	size = size_env(env);
	envp = ft_calloc(size + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		envp[i] = join_name_value(tmp);
		if (envp[i] == NULL)
		{
			free_double(envp);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
