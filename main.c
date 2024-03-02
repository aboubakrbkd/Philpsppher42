/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:57:58 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/02 19:39:57 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	parse_argument_and_fill(char **argv, t_table *philo)
{
	int i = 0;
	while (argv[i])
	{
		if (is_integer(argv[i]) || check_higher(argv[i]) || is_negative(argv[i]))
			print_error();
		i++;
	}
	philo->philo_nbr = ft_atoi(argv[0]);
	philo->time_to_die = ft_atoi(argv[1]);
	philo->time_to_eat = ft_atoi(argv[2]);
	philo->time_to_sleep = ft_atoi(argv[3]);
	if (argv[4])
		philo->number_of_meals = ft_atoi(argv[4]);
	else
		philo->number_of_meals = 0;
}

void	*initialize_philos(t_table *philo)
{
	int i = 0;
	while (i < philo->philo_nbr)
	{
		philo->philo[i].must_eat = philo->number_of_meals;
		philo->philo[i].time_to_eat = 0;
		philo->philo[i].id = i + 1;
		philo->philo[i].right_fork = i;
		philo->philo[i].left_fork = (i + 1) % philo->philo_nbr;
		philo->philo[i].table = philo;
		i++;
	}
	return (NULL);
}
void	*initialize_forks_mutex(t_table *philo)
{
	int i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(philo->meal, NULL);
	pthread_mutex_init(philo->log, NULL);
	return (NULL);
}
void	*initialize_data(t_table *philo)
{
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->philo_nbr);
	if (!philo->forks)
		return (NULL);
	philo->philo = malloc(sizeof(t_table) * philo->philo_nbr);
	if (!philo->philo)
		return (NULL);
	philo->log = malloc(sizeof(pthread_mutex_t));
	if (!philo->log)
		return (NULL);
	philo->meal = malloc(sizeof(pthread_mutex_t));
	if (!philo->meal)
		return (NULL);
	initialize_philos(philo);
	initialize_forks_mutex(philo);
	return (NULL);
	
}
int main(int argc, char **argv)
{
	t_table philo;
	if (argc != 5 && argc != 6)
	{
		printf("not enough\n");
		exit(1);
	}
	else 
	{
		parse_argument_and_fill(argv + 1, &philo);
		initialize_data(&philo);
	}
}

