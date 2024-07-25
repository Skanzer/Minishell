/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:23:19 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/24 17:07:02 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_interrupt = 0;

static int	run_shell(t_minishell *minishell)
{
	int	ret;

	ret = 0;
	while (1)
	{
		reset_var(minishell);
		ret = step_read(minishell);
		if (ret == 0)
			return (0);
		else if (ret == -1)
			continue ;
		if (error_check(minishell->input) == 1)
			continue ;
		else
		{
			ret = step_no_input_error(minishell);
			if (ret == 0)
				return (0);
			else if (ret == 1)
				continue ;
			step_reinit(minishell);
		}
	}
	return (ret);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	if (init_shell(&minishell, env, argc, argv) == ALLOC_ERROR)
		return (free_print_shell(&minishell), 1);
	else
	{
		if (run_shell(&minishell) == 0)
			return (0);
	}
	return (0);
}
