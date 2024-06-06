/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:20:23 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/06 14:35:08 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error_msg(char *msg)
{
	char	*error_msg;
	char 	*tmp;

	tmp = ft_strjoin("Minishell: ", msg);
	if (!tmp)
		return ;
	error_msg = ft_strjoin(tmp, ": ");
	free(tmp);
	if (!error_msg)
		return ;
	printf("%s command not found\n", error_msg);
	free (error_msg);
}
