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
