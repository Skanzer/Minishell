/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:10:37 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/29 17:19:25 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**@brief This function assigns the type of the token
 * @param tokens the tokens struct
*/
static void	put_type(t_tokens *tokens)
{
	if (ft_strcmp(tokens->token, ">") == 0)
		tokens->type = REDIR_OUT;
	else if (ft_strcmp(tokens->token, ">>") == 0)
		tokens->type = REDIR_APPEND;
	else if (ft_strcmp(tokens->token, "<") == 0)
		tokens->type = REDIR_IN;
	else if (ft_strcmp(tokens->token, "<<") == 0)
		tokens->type = HEREDOC;
	else
		tokens->type = WORD;
}
/**@brief This function puts the tokens into the tokens struct
 * @param commands the commands struct
 * @param split the splited input
*/
static int	put_tokens(t_commands *commands, char **split)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	commands->tokens = ft_calloc(1, sizeof(t_tokens));
	if (!commands->tokens)
		return (ALLOC_ERROR);
	tmp = commands->tokens;
	while (split[i])
	{
		tmp->next = NULL;
		tmp->token = ft_calloc((ft_strlen(split[i]) + 1), sizeof(char));
		if (!tmp->token)
			return (ALLOC_ERROR);
		ft_strcpy(tmp->token, split[i]);
		put_type(tmp);
		i++;
		if (!split[i])
			break ;
		tmp->next = ft_calloc(1, sizeof(t_tokens));
		if (!tmp->next)
			return (ALLOC_ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
/**@brief This function creates the tokens struct
 * and puts the splited input into the tokens struct
 * and assigns the type of the token
*/
int	create_tokens(t_commands *commands)
{
	char	c[] = " \t\n\v\f\r";
	char	**split;
	t_commands	*tmp;

	tmp = commands;
	while (tmp)
	{
		split = ft_split_new(tmp->command, c);
		if (!split)
			return (ALLOC_ERROR);
		if (put_tokens(tmp, split) == ALLOC_ERROR)
			return (ALLOC_ERROR);
		if (quotes_deleter_all(tmp) == ALLOC_ERROR)
			return (ALLOC_ERROR);
		tmp = tmp->next;
		free_double(split);
	}
	return (SUCCESS);
}
