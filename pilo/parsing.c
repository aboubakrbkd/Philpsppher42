/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:27:03 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/26 00:38:22 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	print_error(void)
{
	printf("Error\n");
	return (1);
}

long	ft_atoi(char *str)
{
	long	r;
	int		i;
	int		s;

	r = 0;
	i = 0;
	s = 1;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * s);
}

int	is_integer(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	is_negative(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (1);
	return (0);
}

int	check_higher(char *str)
{
	long	result;

	result = ft_atoi(str);
	if (result > INT_MAX || result < INT_MIN)
		return (1);
	return (0);
}
