/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:37:17 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/27 15:17:45 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*get_env_addr(t_commands *cmd, char *var)
{
	t_env	*tmp;

	tmp = cmd->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	remove_env_var(t_minishell *mini, t_env *var)
{
	t_env	*tmp;

	tmp = mini->env;
	free(var->name);
	free(var->value);
	if (tmp == var)
	{
		mini->env = tmp->next;
		free(var);
	}
	else
	{
		while (tmp->next != var)
			tmp = tmp->next;
		tmp->next = var->next;
		free(var);
	}
}

int	unset_builtin(t_minishell *mini)
{
	int		i;
	int		ret;
	t_env	*tmp;
	char	**args;

	ret = SUCCESS;
	i = 1;
	args = mini->commands->cmd_args;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			error_msg("unset", "not a valid identifier", EXIT_FAILURE);
			ret = EXIT_FAILURE;
		}
		else
		{
			tmp = get_env_addr(mini->commands, args[i]);
			if (tmp)
				remove_env_var(mini, tmp);
		}
		i++;
	}
	return (ret);
}
