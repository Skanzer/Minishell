/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:20:23 by szerzeri          #+#    #+#             */
/*   Updated: 2024/05/31 23:26:34 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error_msg(char *msg)
{
	char	*error_msg;

	error_msg = ft_strjoin("Minishell: ", msg);
	if (!error_msg)
		return ;
	perror(error_msg);
	free (error_msg);
}
