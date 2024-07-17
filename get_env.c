/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:48:40 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/09 16:52:47 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**This function calculate the length of the name
 * and the value of the variable env
*/
static void	len_v_and_n(char *env, int *name_len, int *value_len)
{
	int	i;

	i = 0;
	*name_len = 0;
	*value_len = 0;
	while (env[i] != '=')
	{
		(*name_len)++;
		i++;
	}
	i++;
	while (env[i])
	{
		(*value_len)++;
		i++;
	}
}

/**This function copy the name
 * and the value of the variable env
 * into the the new t_env structure
*/
static void	copy_v_and_n(char *env_var, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_var[i] != '=')
	{
		env->name[i] = env_var[i];
		i++;
	}
	env->name[i] = '\0';
	i++;
	while (env_var[i])
	{
		env->value[j] = env_var[i];
		i++;
		j++;
	}
	env->value[j] = '\0';
}

/**This function copy the name and value of the env variable
 * and put them in the t_env structure
 * Memory will be allocated for each variable
*/
static int	copy_env(t_env *env, char *env_var)
{
	int	name_len;
	int	value_len;

	len_v_and_n(env_var, &name_len, &value_len);
	env->name = malloc(sizeof(char) * (name_len + 1));
	if (!env->name)
		return (ALLOC_ERROR);
	env->value = malloc(sizeof(char) * (value_len + 1));
	if (!env->value)
		return (ALLOC_ERROR);
	copy_v_and_n(env_var, env);
	env->next = NULL;
	return (SUCCESS);
}

/**This function copy the env variables and put them in a list
 * Memory will be allocated for each variable
 * and then added to the list
*/
int	get_env(t_minishell *mini, char **env)
{
	int		i;
	t_env	*copy;

	i = 0;
	copy = mini->env;
	while (env[i])
	{
		if (copy_env(copy, env[i]) == ALLOC_ERROR)
			return (free_env(mini), ALLOC_ERROR);
		i++;
		if (!env[i])
			break ;
		copy->next = ft_calloc(1, sizeof(t_env));
		if (!copy->next)
			return (free_env(mini), ALLOC_ERROR);
		copy = copy->next;
	}
	return (SUCCESS);
}
