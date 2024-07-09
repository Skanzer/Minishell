/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:23:31 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/28 17:48:30 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_env_var_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (0);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	printf_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("declare -x %s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static char	**get_var(char *arg)
{
	char	**tmp;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof * tmp * (2 + 1));
	if (!tmp)
		return (NULL);
	tmp[0] = ft_substr(arg, 0, eq_pos - arg);
	tmp[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos));
	tmp[2] = NULL;
	return (tmp);
}

int	set_env_var(char **var, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var[0]) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(var[1]);
			return (SUCCESS);
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp->next = ft_calloc(1, sizeof(t_env));
	if (!tmp->next)
		return (ALLOC_ERROR);
	tmp->next->name = ft_strdup(var[0]);
	tmp->next->value = ft_strdup(var[1]);
	tmp->next->next = NULL;
	return (SUCCESS);
}

int	export_builtin(t_commands *cmd)
{
	int		ret;
	int		i;
	char	**args;
	char	**var;

	ret = SUCCESS;
	i = 1;
	args = cmd->cmd_args;
	if (!args[i])
		return (printf_env(cmd->env));
	while (args[i])
	{
		if (is_valid_env_var_key(args[i]) == 0)
		{
			printf("Minishell: export: `%s': not a valid identifier\n", args[i]);
			ret = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			var = get_var(args[i]);
			set_env_var(var, cmd->env);
			free_double(var);
		}
		i++;
	}
	return (ret);
}
