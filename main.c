/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:23:19 by szerzeri          #+#    #+#             */
/*   Updated: 2024/02/14 13:24:38 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)//int argc, char **argv, char **env
{
	//char	**copy_env;
	char	*input;
	int		i;

	while (1)
	{
		i = 0;
		input = read_input();
		printf("%s\n", input);
		error_check(input);
		input_expansion(input);
		/*while (input[i])
		{
			printf("%s\n", input[i]);
			i++;
		}
		test = tokens(input);
		i = 0;
		while (test[i])
		{
			printf("tokens[%i] = %s\n", i, test[i]);
			i++;
		}
		free_double(input, 0);*/
	}
	exit(EXIT_SUCCESS);
	return (0);
}
