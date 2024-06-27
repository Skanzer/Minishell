/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:51:29 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/19 20:44:23 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**This function colors the different parts
 * of the prompt
 * it takes the name, the color and the character
 * that separates the name from the next part
*/
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
	free(tmp);
	if (!colored)
		return (NULL);
	return (colored);
}

/**This function joins the Path and
 * the $ character to the colored prompt
 * and have the final prompt
*/
static char	*join_prompt(char *prompt, t_minishell *mini)
{
	char	*tmp;
 
	tmp = ft_strjoin(prompt, mini->pwd);
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

/**This function create the prompt
 * it colors the username and hostname
 * adds them together and adds the current directory
*/
static char	*bash_prompt(t_minishell *mini)
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
	prompt = join_prompt(prompt, mini);
	if (!prompt)
		return (NULL);
	return (prompt);
}

/**This function fixes the bug known as the "line wrap" bug
 * by adding the \001 and \002 characters to the prompt
*/
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

/** This function reads the input from the user and returns it
 * first it prepares the prompt and colors it
 * then it reads the input and adds it to the history
*/
char	*read_input(t_minishell *mini)
{
	char	*input;
	char	*prompt;

	prompt = bash_prompt(mini);
	if (!prompt)
		return (NULL);
	prompt = color_work(prompt);
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	free(prompt);
	if (!input)
		return (NULL);
	if (join_input_pipe(input) == ALLOC_ERROR)
		return (NULL);
	add_history(input);
	return (input);
}
