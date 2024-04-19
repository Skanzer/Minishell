/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:02:37 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/19 14:56:08 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**pipe_spliter(char *input)
{
	char	**split;

	split = ft_split_new(input, '|');
    if (!split)
		return (NULL);
	return (split);
}

static int	put_commands(t_minishell *mini, char **split)
{
	t_commands	*tmp;
	int			i;

	i = 0;
	mini->commands = ft_calloc(1, sizeof(t_commands));
	if (!mini->commands)
		return (ALLOC_ERROR);
	tmp = mini->commands;
	while (split[i])
	{
		tmp->command = ft_calloc((ft_strlen(split[i]) + 1), sizeof(char));
		if (!tmp->command)
			return (ALLOC_ERROR);
		ft_strcpy(tmp->command, split[i]);
		i++;
		if (!split[i])
		{
			tmp->next = NULL;
			break ;	
		}
		tmp->next = ft_calloc(1, sizeof(t_commands));
		if (!tmp->next)
			return (ALLOC_ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	tokenizer(t_minishell *mini)
{
    char    	**split;
	int			i = 0;
	t_commands	*tmp;

	split = pipe_spliter(mini->input);
    if (split == NULL)
		return (ALLOC_ERROR);
	if (put_commands(mini, split) == ALLOC_ERROR)
	{
		free_double(split);
		return (ALLOC_ERROR);
	}
	free_double(split);
	
	
	
    return (SUCCESS);
}
