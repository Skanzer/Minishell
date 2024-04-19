/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:51:41 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/19 14:33:17 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_lenstr(t_string *string)
{
    int len;
    t_string *head;

    len = 0;
    head = string;
    while (head)
    {
        len++;
        head = head->next;
    }
    return (len);
}

int replace_command(t_commands  *commands, t_string *string)
{
    char        *new_command;
    t_string    *head;
    int         len;
    int         i;

    i = 0;
    len = ft_lenstr(string);
    new_command = ft_calloc(len + 1, sizeof(char));
    if (!new_command)
    {
        free_string(string);
        return (ALLOC_ERROR);
    }
    head = string;
    while (head)
    {
        new_command[i++] = head->c;
        head = head->next;
    }
    new_command[i] = '\0';
    free_string(string);
    free(commands->command);
    commands->command = new_command;
    return (SUCCESS);
}
