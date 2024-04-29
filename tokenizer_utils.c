/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:17:48 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/22 21:27:13 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief this function adds a space before the redirections
 */
static int	add_space_before(t_string *head)
{
	t_string	*tmp;

	if (head->previous && space_char(head->previous->c) != 1)
	{
		tmp = ft_calloc(1, sizeof(t_string));
		if (!tmp)
			return (ALLOC_ERROR);
		tmp->c = ' ';
		tmp->previous = head->previous;
		tmp->next = head;
		head->previous->next = tmp;
		head->previous = tmp;
	}
	return (SUCCESS);
}
/**
 * @brief This function adds a space after the redirections
 */
static int	add_space_after(t_string *head)
{
	t_string	*tmp;

	if (head->next && space_char(head->next->c) != 1)
	{
		tmp = ft_calloc(1, sizeof(t_string));
		if (!tmp)
			return (ALLOC_ERROR);
		tmp->c = ' ';
		tmp->previous = head;
		tmp->next = head->next;
		head->next->previous = tmp;
		head->next = tmp;
	}
	return (SUCCESS);
}
/**
 * @brief This function adds a space before and after the redirections 
 */
static int	space_adder(t_string *string)
{
	t_string	*head;

	head = string;
	while (head)
	{
		if (head->c == '<' || head->c == '>')
		{
			if (add_space_before(head) == ALLOC_ERROR)
				return (ALLOC_ERROR);
			if (head->next->c == head->c)
				head = head->next;
			if (add_space_after(head) == ALLOC_ERROR)
				return (ALLOC_ERROR);
		}
		head = head->next;
	}
	return (SUCCESS);
}
/**
 * @brief This function puts the command in a linked list
 */
static t_string	*put_in_list(char *command)
{
	t_string	*head;
	t_string	*string;
	int			i;

	i = 0;
	head = ft_calloc(1, sizeof(t_string));
	if (!head)
		return (NULL);
	head->previous = NULL;
	string = head;
	while (command[i])
	{
		string->c = command[i];
		if (!command[i + 1])
		{
			string->next = NULL;
			break ;
		}
		string->next = ft_calloc(1, sizeof(t_string));
		if (!string->next)
			return (NULL);
		string->next->previous = string;
		string = string->next;
		i++;
	}
	return (head);
}
/** 
 * @brief This function replaces the command in the t_commands struct with the new command
 * it takes the command, put in a linked list, add spaces before and after the redirections
 * and then replaces the command in the t_commands struct with the new command
 */
int organize_commands(t_commands *commands)
{
    t_string	*string;
    t_commands	*tmp;

    tmp = commands;
    while (tmp)
    {
        string = put_in_list(tmp->command);
        if (!string)
            return (ALLOC_ERROR);
        if (space_adder(string) == ALLOC_ERROR)
		{
			free_string(string);
            return (ALLOC_ERROR);
		}
        if (replace_command(tmp, string) == ALLOC_ERROR)
		{
			free_string(string);
			return (ALLOC_ERROR);
		}
        tmp = tmp->next;
    }
    return (SUCCESS);
}
