/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:26:00 by szerzeri          #+#    #+#             */
/*   Updated: 2023/01/12 13:50:47 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		len_s1;
	int		len_s2;
	int		i;
	int		j;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	j = 0;
	join = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!join)
		return (NULL);
	while (j < len_s1)
		join[i++] = s1[j++];
	j = 0;
	while (j < len_s2)
		join[i++] = s2[j++];
	join[i] = '\0';
	return (join);
}
