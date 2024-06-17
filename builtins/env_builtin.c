#include "minishell.h"

int	env_builtin(t_commands *cmd)
{
	t_env	*tmp;

	if (cmd->builtin[1])
		return (error_msg("env", "too many argumemts", EXIT_FAILURE);
	tmp = cmd->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

