/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:23:19 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/29 15:35:38 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_memory(t_minishell *minishell)
{
	minishell->env = ft_calloc(1, sizeof(t_env));
	if (!minishell->env)
		return (ALLOC_ERROR);
	minishell->input = NULL;
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
			if (input_expansion(&minishell) == ALLOC_ERROR)
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
			free_commands(minishell.commands);
			free(minishell.input);
		}
	}
	return (0);
}
