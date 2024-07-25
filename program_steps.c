/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_steps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:29:49 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/24 16:20:24 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	step_read(t_minishell *mini)
{
	mini->input = read_input(mini);
	if (g_interrupt == 1)
	{
		free(mini->input);
		return (-1);
	}
	if (!mini->input)
	{
		printf("exit, rd\n");
		free_shell(mini);
		return (0);
	}
	return (1);
}

int	step_expansion(t_minishell *mini)
{
	mini->input = input_expansion(mini->input, mini->env, mini->exit_status);
	if (mini->input == NULL)
	{
		printf("exit, ex\n");
		free_shell(mini);
		return (0);
	}
	return (1);
}

int	step_tokenizer(t_minishell *mini)
{
	if (tokenizer(mini) == ALLOC_ERROR)
	{
		printf("exit, tkn");
		free_shell(mini);
		return (0);
	}
	return (1);
}

int	step_heredoc(t_minishell *mini)
{
	if (heredoc(mini->commands) == ALLOC_ERROR)
	{
		printf("exit, hr\n");
		step_reinit(mini);
		return (1);
	}
	if (g_interrupt == 1)
	{
		free_commands(mini->commands);
		mini->commands = NULL;
		free(mini->input);
		mini->input = NULL;
		return (1);
	}
	return (2);
}

int	step_redir(t_minishell *mini)
{
	if (input_redir(mini->commands) == 1)
	{
		mini->exit_status = 1;
		free_commands(mini->commands);
		free(mini->input);
		return (1);
	}
	if (output_redir(mini->commands) == 1)
	{
		free_commands(mini->commands);
		free(mini->input);
		return (1);
	}
	if (append_redir(mini->commands) == 1)
	{
		free_commands(mini->commands);
		free(mini->input);
		return (1);
	}
	last_redir(mini->commands);
	return (0);
}
