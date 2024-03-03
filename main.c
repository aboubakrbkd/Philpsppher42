/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:57:58 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/02 20:48:51 by aboukdid         ###   ########.fr       */
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
		philo->must_eat_count = ft_atoi(argv[4]);
	else
		philo->must_eat_count = -1;
	philo->time_of_death = 0;
	philo->id_of_the_philo_died = 0;
}

int initialize_philos(t_table *philo)
{
	int i = 0;
	while (i < philo->philo_nbr)
	{
		philo->philo[i].must_eat = philo->must_eat_count;
		philo->philo[i].times_ate = 0;
		philo->philo[i].pos = i + 1;
		philo->philo[i].fr_fork = i;
		philo->philo[i].sc_fork = (i + 1) % philo->philo_nbr;
		philo->philo[i].table = philo;
		i++;
	}
	return (0);
}
int initialize_forks_mutexex(t_table *philo)
{
	int i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(philo->meal, NULL);
	pthread_mutex_init(philo->log, NULL);
	return (0);
}
int	initialize_data(t_table *philo)
{
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->philo_nbr);
	philo->philo = malloc(sizeof(t_philo) * philo->philo_nbr);
	philo->log = malloc(sizeof(pthread_mutex_t));
	philo->meal = malloc(sizeof(pthread_mutex_t));
	initialize_philos(philo);
	initialize_forks_mutexex(philo);
	return (0);
}

int start_dinner(t_table *philo)
{
	
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
		start_dinner(&philo);
	}
}

