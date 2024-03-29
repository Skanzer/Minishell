/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:48:40 by szerzeri          #+#    #+#             */
/*   Updated: 2024/01/31 11:31:43 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**alloc_copy_env(char **env)
{
	int		i;
	char	**copy;

	i = 0;
	while (env[i])
		i++;
	copy = (char **)malloc((i + 1) * sizeof(char *));
	if (!copy)
	{
		free(copy);
		return (NULL);
	}
	i = 0;
	while (env[i])
	{
		copy[i] = (char *)malloc((ft_strlen(env[i]) + 1) * sizeof(char));
		if (!copy[i])
		{
			free_double(copy, i);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

char	**get_env(char **env)
{
	int		i;
	int		j;
	char	**copy;

	copy = alloc_copy_env(env);
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			copy[i][j] = env[i][j];
			j++;
		}
		copy[i][j] = '\0';
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
