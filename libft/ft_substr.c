/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:55:05 by szerzeri          #+#    #+#             */
/*   Updated: 2023/01/23 18:55:54 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	un_strlen(const char *s)
{
	unsigned int	count;

	count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*substring;
	unsigned int		i;
	unsigned int		j;

	i = start;
	j = 0;
	if (start >= un_strlen(s))
	{
		substring = (char *)malloc(sizeof(char) * 1);
		if (!substring)
			return (NULL);
		*substring = '\0';
		return (substring);
	}
	if (len >= un_strlen(s))
		substring = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	while (j < len && s[i] != '\0')
		substring[j++] = s[i++];
	substring[j] = '\0';
	return (substring);
}
