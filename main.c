/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:23:19 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/01 16:11:50 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell(t_minishell *minishell, char **env, int argc, char **argv)
{
	if (argc != 1)
	{
		printf("argv[0]: %s is the only argument needed to run minishell\n", argv[0]);
		return (1);		
	}
	get_env(minishell, env);
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
		free_env(&minishell);
		return (1);
	}
	while (1)
	{
		minishell.input = read_input();
		if (error_check(minishell.input) == 1)
		{
			free(minishell.input);
			return (0);
		}
		minishell.input = input_expansion(minishell.input, minishell.env);
		printf("%s\n", minishell.input);
		free(minishell.input);
	}
	exit(EXIT_SUCCESS);
	return (0);
}
