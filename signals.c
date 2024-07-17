/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:08:27 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/15 17:17:56 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	interrupt = 1;
	rl_replace_line("", 0);
	rl_done = 1;
	write(1, "\n", 1);
}

void	sig_quit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	sig_handler(void)
{
	struct sigaction	sa;

	sig_quit();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sigint_handler;
	sigaction(SIGINT, &sa, NULL);
}
