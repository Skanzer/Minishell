/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:38:07 by szerzeri         #+#    #+#             */
/*   Updated: 2024/03/31 21:39:13 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_env(t_minishell *minishell)
{
    t_env   *tmp;

    while (minishell->env)
    {
        tmp = minishell->env;
        minishell->env = minishell->env->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
    }
}

void    free_commands(t_commands *commands)
{
    t_commands  *tmp;

    while (commands)
    {
        tmp = commands;
        commands = commands->next;
        free(tmp->command);
        if (tmp->tokens)
            free_tokens(tmp->tokens);
        free(tmp);
    }
}

void	free_double(char **array)
{
    int i;

    i = 0;
	if (!array)
		return;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void    free_shell(t_minishell *minishell)
{
    if (minishell->input)
        free(minishell->input);
    free_env(minishell);
    free_commands(minishell->commands);
}

void    free_string(t_string *string)
{
    t_string    *tmp;

    while (string)
    {
        tmp = string;
        string = string->next;
        free(tmp);
    }
}
