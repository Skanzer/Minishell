/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:24:31 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/03 13:28:12 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_wordcount_util(char *str, int *i)
{
	char	quote;

	quote = str[*i];
	if (quote == '\'' || quote == '"')
	{
		*i += 1;
		while (str[*i] != quote && str[*i] != '\0')
			*i += 1;
	}
}

void    ft_stralloc_util(char *str, int *k, int *i)
{
	char	quote;

	quote = str[*k];
	if (quote == '\'' || quote == '"')
	{
		*k += 1;
		*i += 1;
		while (str[*k] != quote && str[*k] != '\0')
		{
			*i += 1;
			*k += 1;
		}
	}
	*k += 1;
	*i += 1;
}
