/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:02:37 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/10 13:10:59 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_spliter(char **split, char *input)
{
	split = ft_split_new(input, '|');
    if (!split)
	{
		free_double(split, ft_wordcount(input, '\'') - 1);
		return (ALLOC_ERROR);	
	}
	return (SUCCESS);
}

static int	put_commands(t_minishell *mini, char **split)
{
	t_commands	*tmp;
	int			i;

	i = 0;
	tmp = mini->commands;
	while (split[i])
	{
		printf("lenna\n");
		tmp->command = malloc(sizeof(char) * (ft_strlen(split[i]) + 1));
		if (!tmp->command)
			return (ALLOC_ERROR);
		ft_strcpy(tmp->command, split[i]);
		i++;
		if (!split[i])
		{
			tmp->next = NULL;
			break ;	
		}
		tmp->next = malloc(sizeof(t_commands));
		if (!tmp->next)
			return (ALLOC_ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	tokenizer(t_minishell *mini)
{
    char    	**split;

	split = NULL;
    if (pipe_spliter(split, mini->input) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	if (put_commands(mini, split) == ALLOC_ERROR)
		return (ALLOC_ERROR);
    return (SUCCESS);
}
