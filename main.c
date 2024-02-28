/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:57:58 by aboukdid          #+#    #+#             */
/*   Updated: 2024/02/28 09:03:04 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	parse_argument(char **argv, int argc, t_list *philo)
{
	int i = 0;
	while (argv[i])
	{
		if (is_integer(argv[i]) || check_higher(argv[i]) || is_negative(argv[i]))
			print_error();
		i++;
	}
}
int main(int argc, char **argv)
{
	t_list *philo = malloc(sizeof(t_list));
	if (!philo)
		return(0);
	if (argc != 5 && argc != 6)
	{
		printf("not enough\n");
		exit(1);
	}
	else 
	{
		parse_argument(argv + 1, argc, philo);
		philo->num_philo = ft_atoi(argv[1]);
		philo->time_to_die = ft_atoi(argv[2]);
		philo->time_to_eat = ft_atoi(argv[3]);
		philo->time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			philo->number_of_meals = ft_atoi(argv[5]);
		else
			philo->number_of_meals = 0;
	}
}
