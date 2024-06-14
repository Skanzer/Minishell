/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:20:23 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/14 17:05:33 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_msg(char *cmd, char *msg, int error_nb)
{
	char	*error_msg;
	char 	*tmp;

	error_msg = ft_strjoin("Minishell: ", cmd);
	tmp = ft_strjoin(error_msg, ": ");
	free(error_msg);
	error_msg = ft_strjoin(tmp, msg);
	free(tmp);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	free (error_msg);
	return (error_nb);
}
