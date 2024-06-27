/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:04:05 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/19 19:00:30 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_commands *commands)
{
	t_commands	*tmp;

	while (commands)
	{
		tmp = commands;
		commands = commands->next;
		free(tmp->command);
		if (tmp->tokens)
			free_tokens(tmp->tokens);
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		if (tmp->cmd_args)
			free_double(tmp->cmd_args);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		if (tmp->append)
			free(tmp->append);
		if (tmp->heredoc)
			free(tmp->heredoc);
		free(tmp);
	}
}
