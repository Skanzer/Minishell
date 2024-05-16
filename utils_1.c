/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:37:25 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/16 17:11:43 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_first(t_tokens *tokens, t_token_type type)
{
	t_tokens	*tmp;

	while (tokens->type == type)
	{
		tmp = tokens;
		tokens = tokens->next->next;
		free(tmp->token);
		free(tmp->next->token);
		free(tmp->next);
		free(tmp);
	}
}

void	delete_token_node(t_tokens *tokens, t_token_type type)
{
	t_tokens	*tmp;
	t_tokens	*prev;

	delete_first(tokens, type);
	tmp = tokens->next;
	prev = tokens;
	while (tmp)
	{
		if (tmp->type == type)
		{
			prev->next = tmp->next->next;
			free(tmp->token);
			free(tmp->next->token);
			free(tmp->next);
			free(tmp);
			tmp = prev->next;
			continue ;
		}
		tmp = tmp->next;
		prev = prev->next;
	}
}
