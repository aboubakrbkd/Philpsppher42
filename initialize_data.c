/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:48:08 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/04 13:49:33 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	initialize_philos(t_table *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_nbr)
	{
		philo->philo[i].must_eat = philo->number_of_meals;
		philo->philo[i].times_ate = 0;
		philo->philo[i].id = i + 1;
		philo->philo[i].first_fork = i;
		philo->philo[i].second_fork = (i + 1) % philo->philo_nbr;
		philo->philo[i].table = philo;
		i++;
	}
	return (0);
}

int	initialize_forks_mutexex(t_table *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(philo->meal, NULL);
	return (0);
}

int	initialize_data(t_table *philo)
{
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->philo_nbr);
	philo->philo = malloc(sizeof(t_philo) * philo->philo_nbr);
	philo->meal = malloc(sizeof(pthread_mutex_t));
	initialize_philos(philo);
	initialize_forks_mutexex(philo);
	return (0);
}

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
