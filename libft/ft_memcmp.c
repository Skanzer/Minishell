/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:43:20 by szerzeri          #+#    #+#             */
/*   Updated: 2022/12/15 17:10:25 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	m;

	while (n--)
	{
		m = *(const unsigned char *)s1++ - *(const unsigned char *)s2++;
		if (m != 0)
			return (m);
	}
	return (0);
}
