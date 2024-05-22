/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:48:35 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/22 11:10:10 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function opens a file with the given filename and flags
 * and then closes the fd.
 * It is used for the case of multiple output redirections,
 * so the file is created but not written to.
 */
static int	create_file(char *filename)
{
	int	fd;

	fd = open_file(filename, 1);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	close(fd);
	return (0);
}

/**
 * @brief This function puts the name of the file in the outfile variable 
 * in the comand struct.
 */
static int	put_outfile(t_commands *command, t_tokens *token)
{
	if (token->type == REDIR_OUT)
	{
		if (command->outfile)
			free(command->outfile);
		command->outfile = ft_strdup(token->next->token);
		if (!command->outfile)
			return (ALLOC_ERROR);
	}
	else
	{
		if (command->append)
			free(command->append);
		command->append = ft_strdup(token->next->token);
		if (!command->append)
			return (ALLOC_ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief This function go through each token struct in each command
 * and checks if there is a token with the type REDIR_OUT.
 * If there is multiple tokens with the type REDIR_OUT,
 * it creates a file for each token except the last one.
 */
int	output_redir(t_commands *commands)
{
	t_tokens	*token;
	t_commands	*tmp;

	tmp = commands;
	while (tmp)
	{
		token = find_token(tmp->tokens, REDIR_OUT);
		while (token)
		{
			if (put_outfile(tmp, token))
				return (ALLOC_ERROR);
			token = find_token(token->next, REDIR_OUT);
			if (!token)
				break ;
			else
			{
				if (create_file(tmp->outfile))
					return (ALLOC_ERROR);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

/**
 * @brief This function go through each token struct in each command
 * and checks if there is a token with the type REDIR_APPEND.
 * If there is multiple tokens with the type REDIR_APPEND,
 * it creates a file for each token except the last one.
 */
int	append_redir(t_commands *commands)
{
	t_tokens	*token;
	t_commands	*tmp;

	tmp = commands;
	while (tmp)
	{
		token = find_token(tmp->tokens, REDIR_APPEND);
		while (token)
		{
			if (put_outfile(tmp, token))
				return (ALLOC_ERROR);
			token = find_token(token->next, REDIR_APPEND);
			if (!token)
				break ;
			else
			{
				if (create_file(tmp->append))
					return (ALLOC_ERROR);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
