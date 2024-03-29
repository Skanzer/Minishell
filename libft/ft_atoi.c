/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:06:01 by szerzeri          #+#    #+#             */
/*   Updated: 2023/01/10 13:43:30 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;
	int	count_sign;

	i = 0;
	sign = 1;
	result = 0;
	count_sign = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		if (count_sign++ == 1)
			return (0);
		i++;
	}
	while (str[i] <= 57 && str[i] >= 48)
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}
