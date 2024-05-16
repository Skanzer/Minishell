/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_deleter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:45:17 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/16 17:24:37 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_without_quotes(char *token, char *new_token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i] != '\0')
	{
		if (token[i] != '\"' && token[i] != '\'')
		{
			new_token[j] = token[i];
			j++;
		}
		i++;
	}
	new_token[j] = '\0';
	return (new_token);
}

int	quotes_deleter(t_tokens *tokens)
{
	int		len;
	char	*new_token;

	if (ft_strchr(tokens->token, '\"') == NULL \
				&& ft_strchr(tokens->token, '\'') == NULL)
		return (SUCCESS);
	len = ft_strlen(tokens->token) - 2;
	new_token = ft_calloc(len + 1, sizeof(char));
	if (new_token == NULL)
		return (ALLOC_ERROR);
	new_token = copy_without_quotes(tokens->token, new_token);
	free(tokens->token);
	tokens->token = new_token;
	return (SUCCESS);
}

/**
 * @brief This function deletes all the quotes from the tokens
 * and if the token is a heredoc it checks if there are quotes
 * if there are quotes it sets the quoted_heredoc flag to 1
 * @param commands the commands struct
 */
int	quotes_deleter_all(t_commands *commands)
{
	t_tokens	*tmp;
	int			ret;

	tmp = commands->tokens;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (ft_strchr(tmp->token, '\"') != NULL \
				|| ft_strchr(tmp->token, '\'') != NULL)
				commands->quoted_heredoc = 1;
		}
		ret = quotes_deleter(tmp);
		if (ret != SUCCESS)
			return (ret);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
