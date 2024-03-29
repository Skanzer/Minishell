/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:18:51 by szerzeri          #+#    #+#             */
/*   Updated: 2023/01/12 21:04:51 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_int_len(int n)
{
	int				count;
	unsigned int	tmp;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		tmp = n * (-1);
	}
	else
		tmp = n;
	while (tmp != 0)
	{
		count++;
		tmp = tmp / 10;
	}
	return (count);
}

char	ft_to_char(unsigned int n)
{
	char	c;

	c = (n % 10) + 48;
	return (c);
}

char	*ft_itoa(int n)
{
	int				len;
	unsigned int	tmp;
	char			*str;

	len = ft_int_len(n);
	tmp = n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		*str = '-';
		tmp = n * (-1);
	}
	str[len] = '\0';
	while (len > 0)
	{
		if (str[len - 1] != '-')
			str[len - 1] = ft_to_char(tmp);
		tmp = tmp / 10;
		len --;
	}
	return (str);
}
