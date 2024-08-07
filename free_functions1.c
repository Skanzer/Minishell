/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:04:05 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/23 15:00:21 by szerzeri         ###   ########.fr       */
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
		if (tmp->command)
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
