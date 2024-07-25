/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_steps_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:55:56 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/24 16:49:07 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	step_execution(t_minishell *mini)
{
	if (create_cmd_args(mini->commands) == ALLOC_ERROR)
	{
		printf("exit\n");
		free_shell(mini);
		return (0);
	}
	if (executor(mini) == ALLOC_ERROR)
	{
		printf("Error: failed to execute command\n");
		free_shell(mini);
		return (0);
	}
	return (1);
}

int	step_no_input_error(t_minishell *mini)
{
	int	ret;

	if (step_expansion(mini) == 0)
		return (0);
	if (mini->input[0] == '\0')
	{
		free(mini->input);
		return (1);
	}
	if (step_tokenizer(mini) == 0)
		return (0);
	ret = step_heredoc(mini);
	if (ret == 0)
		return (0);
	else if (ret == 1)
		return (1);
	if (step_redir(mini) == 1)
		return (1);
	if (step_execution(mini) == 0)
		return (0);
	return (2);
}

void	step_reinit(t_minishell *mini)
{
	mini->index_cmd = -1;
	if (mini->pipe_fd)
	{
		close_pipe_fd(mini);
		free_pipe(mini, mini->pipe_fd);
	}
	if (mini->commands)
		free_commands(mini->commands);
	free(mini->input);
	mini->input = NULL;
	mini->pipe_fd = NULL;
	mini->index_cmd = 0;
	mini->nb_cmd = 0;
}

void	reset_var(t_minishell *mini)
{
	g_interrupt = 0;
	rl_done = 0;
	sig_handler();
	mini->commands = NULL;
}
