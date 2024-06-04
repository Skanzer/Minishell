/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:38:40 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/04 14:20:06 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function checks if the file exists and is readable.
 */
static int	check_input_redir(char *input_redir)
{
	if (access(input_redir, F_OK | R_OK) == -1)
	{
		perror(input_redir);
		return (1);
	}
	return (0);
}

/**
 * @brief This function go through each token struct in each command
 * and check if there is a token with the type REDIR_IN.
 * If there is, it checks if the file exists and is readable.
 * If the file does not exist or is not readable, it prints an error message.
 */
int	input_redir(t_commands *commands)
{
	t_tokens	*token;
	t_commands	*tmp;

	tmp = commands;
	while (tmp)
	{
		token = find_token(tmp->tokens, REDIR_IN);
		while (token)
		{
			if (tmp->infile)
				free(tmp->infile);
			tmp->infile = NULL;
			if (check_input_redir(token->next->token) == 1)
				return (1);
			tmp->infile = ft_strdup(token->next->token);
			if (tmp->infile == NULL)
				return (1);
			token = find_token(token->next, REDIR_IN);
		}
		tmp = tmp->next;
	}
	return (0);
}
