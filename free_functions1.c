/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:04:05 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/29 14:05:57 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_tokens(t_tokens *tokens)
{
    t_tokens    *tmp;

    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->token);
        free(tmp);
    }
}
