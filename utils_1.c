/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:37:25 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/19 15:51:25 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens	*delete_first(t_tokens *tokens, t_token_type type)
{
	t_tokens	*tmp;

	while (tokens && tokens->type == type)
	{
		tmp = tokens;
		tokens = tokens->next->next;
		free(tmp->token);
		free(tmp->next->token);
		free(tmp->next);
		free(tmp);
	}
	return (tokens);
}

t_tokens	*delete_token_node(t_tokens *tokens, t_token_type type)
{
	t_tokens	*tmp;
	t_tokens	*prev;

	tokens = delete_first(tokens, type);
	if (!tokens)
		return (NULL);
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
	return (tokens);
}

t_tokens	*find_token(t_tokens *token, t_token_type type)
{
	t_tokens	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == type)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	open_file(char *file_name, int w_r)
{
	int	ret;

	if (w_r == 0)
		ret = open(file_name, O_RDONLY, 0777);
	else if (w_r == 2)
		ret = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		ret = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
		perror(file_name);
	return (ret);
}

void	free_print_shell(t_minishell *mini)
{
	printf("Error: failed to allocate memory for minishell\n");
	free_shell(mini);
}
