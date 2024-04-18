/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:02:37 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/15 14:56:19 by szerzeri         ###   ########.fr       */
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
	t_string	*string;
	t_string	*head;
	t_string	*ras;

	split = pipe_spliter(mini->input);
    if (split == NULL)
		return (ALLOC_ERROR);
	if (put_commands(mini, split) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	tmp = mini->commands;
	head = ft_calloc(1, sizeof(t_string));
	if (!head)
		return (ALLOC_ERROR);
	head->previous = NULL;
	string = head;
	while (tmp->command[i])
	{
		string->c = tmp->command[i];
		if (!tmp->command[i + 1])
		{
			string->next = NULL;
			break ;
		}
		string->next = ft_calloc(1, sizeof(t_string));
		if (!string->next)
			return (ALLOC_ERROR);
		string->next->previous = string;
		string = string->next;
		i++;
	}
	
    return (SUCCESS);
}

int	space_adder(t_string *string)
{
	t_string	*tmp1;

	ras = head;
	while (ras)
	{
		if (ras->c == '<' || ras->c == '>')
		{
			if (ras->previous && space_char(ras->previous->c) != 1)
			{
				tmp1 = ft_calloc(1, sizeof(t_string));
				if (!tmp1)
					return (ALLOC_ERROR);
				tmp1->c = ' ';
				tmp1->previous = ras->previous;
				tmp1->next = ras;
				ras->previous->next = tmp1;
				ras->previous = tmp1;
			}
			if (ras->next->c == ras->c)
				ras = ras->next;
			if (ras->next && space_char(ras->next->c) != 1)
			{
				tmp1 = ft_calloc(1, sizeof(t_string));
				if (!tmp)
					return (ALLOC_ERROR);
				tmp1->c = ' ';
				tmp1->previous = ras;
				tmp1->next = ras->next;
				ras->next->previous = tmp1;
				ras->next = tmp1;
			}
		}
		ras = ras->next;
	}
}