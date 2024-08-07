/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:44:09 by szerzeri          #+#    #+#             */
/*   Updated: 2024/07/09 16:38:48 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_freeup(char *strs)
{
	int	i;

	i = 0;
	while (strs[i] != '\0')
	{
		free(strs);
		i++;
	}
	free(strs);
}

int	ft_wordcount(char *str, char *c)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if (check_c(str[i], c) == 0)
		{
			word++;
			while (check_c(str[i], c) == 0 && str[i] != '\0')
			{
				ft_wordcount_util(str, &i);
				i++;
			}
			if (str[i] == '\0')
				return (word);
		}
		i++;
	}
	return (word);
}

static void	ft_splitcpy(char *word, char *str, char *c, int j)
{
	int		i;
	char	quote;

	i = 0;
	while (str[j] != '\0' && check_c(str[j], c) == 1)
		j++;
	while (check_c(str[j + i], c) == 0 && str[j + i] != '\0')
	{
		quote = str[j + i];
		if (quote == '\'' || quote == '"')
		{
			word[i] = str[j + i];
			i++;
			while (str[j + i] != quote && str[j + i] != '\0')
			{
				word[i] = str[j + i];
				i++;
			}
		}
		word[i] = str[j + i];
		i++;
	}
	word[i] = '\0';
}

static char	*ft_stralloc(char *str, char *c, int *k)
{
	char	*word;
	int		j;
	int		i;

	j = *k;
	i = 0;
	word = NULL;
	while (str[*k] != '\0')
	{
		if (check_c(str[*k], c) == 0)
		{
			while (str[*k] != '\0' && check_c(str[*k], c) == 0)
				ft_stralloc_util(str, k, &i);
			word = (char *)malloc(sizeof(char) * (i + 1));
			if (word == NULL)
				return (free(word), NULL);
			break ;
		}
		*k += 1;
	}
	ft_splitcpy(word, str, c, j);
	return (word);
}

char	**ft_split_new(char const *str, char *c)
{
	char	**strs;
	int		i;
	int		j;
	int		pos;

	if (str == NULL)
		return (NULL);
	i = 0;
	pos = 0;
	j = ft_wordcount((char *)str, c);
	strs = (char **)malloc(sizeof(char *) * (j + 1));
	if (strs == NULL)
		return (free(strs), NULL);
	strs[j] = NULL;
	while (i < j)
	{
		strs[i] = ft_stralloc(((char *)str), c, &pos);
		if (strs[i] == NULL)
		{
			ft_freeup(strs[i]);
		}
		i++;
	}
	return (strs);
}
