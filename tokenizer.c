/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:02:37 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/19 20:15:25 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**@brief This function splits the input according to pipes
 * and returns a double array
 * @param input the input command
 */
static char	**pipe_spliter(char *input)
{
	char	**split;
	char	*c;

	c = "|";
	split = ft_split_new(input, c);
	if (!split)
		return (NULL);
	return (split);
}

/**@brief This function creates and initializes the commands struct
 * and returns the commands struct
 */	
static t_commands	*init_commands(t_minishell *mini)
{
	t_commands	*commands;

	commands = ft_calloc(1, sizeof(t_commands));
	if (!commands)
		return (NULL);
	commands->env = mini->env;
	commands->builtin = 0;
	commands->infile_fd = -1;
	commands->outfile_fd = -1;
	commands->quoted_heredoc = 0;
	commands->exit_status = mini->exit_status;
	return (commands);
}

/**@brief This function creates the commands struct
 * and puts the splited input into the commands struct
 * @param mini the minishell structure
 * @param split the splited input
 */
static int	put_commands(t_minishell *mini, char **split)
{
	t_commands	*tmp;
	int			i;

	i = 0;
	mini->commands = init_commands(mini);
	if (!mini->commands)
		return (ALLOC_ERROR);
	tmp = mini->commands;
	while (split[i])
	{
		tmp->command = ft_calloc((ft_strlen(split[i]) + 1), sizeof(char));
		if (!tmp->command)
			return (ALLOC_ERROR);
		ft_strcpy(tmp->command, split[i]);
		i++;
		tmp->next = NULL;
		if (!split[i])
			break ;
		tmp->next = init_commands(mini);
		if (!tmp->next)
			return (ALLOC_ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

/**@brief this function creates the tokens of the input command 
 * it splits the input into commands according to pipes
 * then it splits the commands into tokens and assigns the type of the token
 * @param mini the minishell structure
*/
int	tokenizer(t_minishell *mini)
{
	char	**split;

	split = pipe_spliter(mini->input);
	if (split == NULL)
		return (ALLOC_ERROR);
	if (put_commands(mini, split) == ALLOC_ERROR)
	{
		free_double(split);
		free_commands(mini->commands);
		return (ALLOC_ERROR);
	}
	free_double(split);
	if (organize_commands(mini->commands) == ALLOC_ERROR || \
		create_tokens(mini->commands) == ALLOC_ERROR)
	{
		free_commands(mini->commands);
		return (ALLOC_ERROR);
	}
	if (after_redir_check(mini->commands) == 1)
	{
		free_commands(mini->commands);
		return (1);
	}
	return (SUCCESS);
}
