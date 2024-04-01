/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:23:19 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/01 15:03:35 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	char		*input;
	

	if (argc != 1)
	{
		printf("argv[0]: %s is the only argument needed to run minishell\n", argv[0]);
		return (0);		
	}
	get_env(&minishell, env);
	if (!minishell.env)
		return (ALLOC_ERROR);
	while (1)
	{
		input = read_input();
		if (error_check(input) == 1)
		{
			free(input);
			return (0);
		}
		input = input_expansion(input, minishell.env);
		free(input);
	}
	exit(EXIT_SUCCESS);
	return (0);
}
