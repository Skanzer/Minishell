/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:23:19 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/29 16:47:51 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_memory(t_minishell *minishell)
{
	minishell->env = ft_calloc(1, sizeof(t_env));
	if (!minishell->env)
		return (ALLOC_ERROR);
	minishell->input = NULL;
	minishell->commands = NULL;
	minishell->pipe_fd = NULL;
	minishell->exit_status = 0;
	minishell->pid = -1;
	minishell->index_cmd = 0;
	minishell->nb_cmd = 0;
	return (0);
}

int	init_shell(t_minishell *minishell, char **env, int argc, char **argv)
{
	if (argc != 1)
	{
		printf("argv[0]: %s is the only argument needed to run minishell\n", argv[0]);
		return (1);		
	}
	if (init_memory(minishell) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	if (get_env(minishell, env) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	if (!minishell->env)
		return (ALLOC_ERROR);
	return (0);
}


int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	//t_commands	*commands;
	//t_tokens	*tokens;

	if (init_shell(&minishell, env, argc, argv) == ALLOC_ERROR)
	{
		printf("Error: failed to allocate memory for minishell\n");
		free_shell(&minishell);
		return (1);
	}
	while (1)
	{
		minishell.input = read_input();
		if (!minishell.input)
		{
			printf("Error: failed to read input\n");
			free_shell(&minishell);
			return (1);
		}
		if (error_check(minishell.input) == 1)
			continue ;
		else
		{
			if (input_expansion(minishell.input, minishell.env) == ALLOC_ERROR)
			{
				printf("Error: failed to expand input\n");
				free_shell(&minishell);
				return (1);
			}
			if (tokenizer(&minishell) == ALLOC_ERROR)
			{
				printf("Error: failed to allocate memory for minishell\n");
				free_shell(&minishell);
				return (1);
			}
			if (heredoc(minishell.commands) == ALLOC_ERROR)
			{
				printf("Error: failed to allocate memory for minishell\n");
				free_shell(&minishell);
				return (1);
			}
			if (input_redir(minishell.commands) == 1)
			{
				free_commands(minishell.commands);
				free(minishell.input);
				continue;
			}
			if (output_redir(minishell.commands) == 1)
			{
				free_commands(minishell.commands);
				free(minishell.input);
				continue;
			}
			last_redir(minishell.commands);
			if (create_cmd_args(minishell.commands) == ALLOC_ERROR)
			{
				printf("Error: failed to allocate memory for minishell\n");
				free_shell(&minishell);
				return (1);
			}
			if (executor(&minishell) == ALLOC_ERROR)
			{
				printf("Error: failed to execute command\n");
				free_shell(&minishell);
				return (1);
			}
			/*commands = minishell.commands;
			while (commands)
			{
				printf("infile: %s\noutfile: %s\nheredoc: %s\n", commands->infile, commands->outfile, commands->heredoc);
				tokens = commands->tokens;
				while (tokens)
				{
					printf("token: %s\n", tokens->token);
					tokens = tokens->next;
				}
				printf("\\\\\\\\////////\n");
				commands = commands->next;
			}*/
			free_commands(minishell.commands);
			minishell.commands = NULL;
			free(minishell.input);
			minishell.input = NULL;
			free_pipe(minishell.pipe_fd);
			minishell.pipe_fd = NULL;
			minishell.index_cmd = 0;
			minisell.nb_cmd = 0;
		}
	}
	return (0);
}
