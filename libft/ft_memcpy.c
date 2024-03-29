/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:17:02 by szerzeri          #+#    #+#             */
/*   Updated: 2023/01/05 17:49:53 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dstc;
	const char	*srccc;

	if ((dest == src) || n == 0)
		return (dest);
	if (!dest && !src)
		return (0);
	dstc = (char *)dest;
	srccc = (const char *)src;
	while (n--)
		dstc[n] = srccc[n];
	return (dest);
}
