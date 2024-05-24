/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:10:57 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/23 10:23:35 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function calls the input_redir, output_redir
 * and append_redir functions.
 * If one of them returns an error, it returns an error.
 */
int	in_app_out_redir(t_commands *commands)
{
	if (input_redir(commands) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	if (output_redir(commands) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	if (append_redir(commands) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	return (SUCCESS);
}

/**
 * @brief This function finds the last token with the type
 * of the redirection.
 * it either returns NULL or the last token with the specified type
 * when type is REDIR_IN, it returns the last REDIR_IN or HEREDOC token
 * when type is REDIR_OUT, it returns the last REDIR_OUT or REDIR_APPEND token
 */
static t_tokens	*find_last_token(t_tokens *tokens, t_token_type type)
{
	t_tokens	*tmp;
	t_tokens	*last;

	tmp = tokens;
	last = NULL;
	while (tmp)
	{
		if (type == REDIR_IN)
		{
			if (tmp->type == REDIR_IN || tmp->type == HEREDOC)
				last = tmp;
		}
		else if (type == REDIR_OUT)
		{
			if (tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND)
				last = tmp;
		}
		tmp = tmp->next;
	}
	return (last);
}

/**
 * @brief This function frees the infile or the heredoc
 * depending on the last type of the token i the command.
 * It also deletes the redir_in, heredoc tokens
 * and the node after them.
 * @param command The command struct.
 * @param token The last token with in_redirection and heredoc.
 */
static void	organize_redir_in(t_commands *command, t_tokens *token)
{
	if (token->type == REDIR_IN)
	{
		if (command->heredoc)
		{
			free(command->heredoc);
			command->heredoc = NULL;
		}
	}
	else if (token->type == HEREDOC)
	{
		if (command->infile)
		{
			free(command->infile);
			command->infile = NULL;
		}
	}
	command->tokens = delete_token_node(command->tokens, REDIR_IN);
	command->tokens = delete_token_node(command->tokens, HEREDOC);
}

/**
 * @brief This function frees the append or the outfile
 * depending on the last type of the token in the command.
 * It also deletes the redir_out, redir_append tokens
 * and the node after them.
 * @param command The command struct.
 * @param token The last token with out/append redirection.
 */
static void	organize_redir_out(t_commands *command, t_tokens *token)
{
	if (token->type == REDIR_OUT)
	{
		if (command->append)
		{
			free(command->append);
			command->append = NULL;
		}
	}
	else if (token->type == REDIR_APPEND)
	{
		if (command->outfile)
		{
			free(command->outfile);
			command->outfile = NULL;
		}
	}
	command->tokens = delete_token_node(command->tokens, REDIR_OUT);
	command->tokens = delete_token_node(command->tokens, REDIR_APPEND);
}

/**
 * @brief This function checks the redirections in each command.
 * It checks which is the last in/output redirection and
 * deletes the other ones.
 * In the end the token struct of each command will only contain
 * the command and the arguments.
 */
void	last_redir(t_commands *commands)
{
	t_commands	*tmp;
	t_tokens	*token_in;
	t_tokens	*token_out;

	tmp = commands;
	while (tmp)
	{
		token_in = find_last_token(tmp->tokens, REDIR_IN);
		if (token_in)
			organize_redir_in(tmp, token_in);
		token_out = find_last_token(tmp->tokens, REDIR_OUT);
		if (token_out)
			organize_redir_out(tmp, token_out);
		tmp = tmp->next;
	}
}
