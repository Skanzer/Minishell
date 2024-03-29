/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:51:29 by szerzeri          #+#    #+#             */
/*   Updated: 2024/02/13 18:23:28 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prompt_color(char *name, char *color, char *c)
{
	char	*colored;
	char	*tmp;

	colored = ft_strjoin(color, name);
	if (!colored)
		return (NULL);
	tmp = ft_strjoin(colored, c);
	free(colored);
	if (!tmp)
		return (NULL);
	colored = ft_strjoin(tmp, ANSI_RESET);
	if (!colored)
		return (NULL);
	free(tmp);
	return (colored);
}

static char	*join_prompt(char *prompt)
{
	char	*tmp;

	tmp = ft_strjoin(prompt, getenv("PWD"));
	free(prompt);
	if (!tmp)
		return (NULL);
	prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	if (!prompt)
		return (NULL);
	tmp = ft_strjoin("\001", prompt);
	free (prompt);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*bash_prompt(void)
{
	char	*username;
	char	*hostname;
	char	*prompt;

	username = prompt_color(USERNAME, ANSI_RED, "@");
	if (!username)
		return (NULL);
	hostname = prompt_color(HOSTNAME, ANSI_YELLOW, ":");
	if (!hostname)
	{
		free (username);
		return (NULL);
	}
	prompt = ft_strjoin(username, hostname);
	free(username);
	free(hostname);
	if (!prompt)
		return (NULL);
	prompt = join_prompt(prompt);
	if (!prompt)
		return (NULL);
	return (prompt);
}

static char	*color_work(char *prompt)
{
	char	*before;
	char	*after;

	before = ft_strjoin("\001", prompt);
	free(prompt);
	if (!before)
		return (NULL);
	after = ft_strjoin(before, "\002");
	free(before);
	if (!after)
		return (NULL);
	return (after);
}

char	*read_input(void)
{
	char	*input;
	char	*prompt;

	prompt = bash_prompt();
	if (!prompt)
		return (NULL);
	prompt = color_work(prompt);
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	free(prompt);
	if (!input)
	{
		free(input);
		exit(EXIT_SUCCESS);
	}
	add_history(input);
	return (input);
}
