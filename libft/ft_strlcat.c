/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:46:19 by szerzeri          #+#    #+#             */
/*   Updated: 2023/01/10 13:48:08 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len_dest;
	unsigned int	len_src;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	j = 0;
	i = len_dest;
	while (src[j] != '\0' && i < size - 1 && size > 0)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (size > len_dest)
		dest[i] = '\0';
	if (size < len_dest)
		return (len_src + size);
	else
		return (len_src + len_dest);
}
