/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:50:15 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/26 14:49:03 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	handle_the_odds(t_philo *philo)
{
	while (philo->must_eat)
	{
		pthread_mutex_lock(&philo->table->forks[philo->first_fork]);
		printf("%ld %d %s\n", get_time() - philo->table->star_time,
			philo->id, FORK);
		pthread_mutex_lock(&philo->table->forks[philo->second_fork]);
		printf("%ld %d %s\n", get_time() - philo->table->star_time,
			philo->id, FORK);
		printf("%ld %d %s\n", get_time() - philo->table->star_time,
			philo->id, EAT);
		if (check_the_routine(philo, philo->table->time_to_eat))
			break ;
		philo->last_time_eat = get_time();
		pthread_mutex_unlock(&philo->table->forks[philo->first_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->second_fork]);
		printf("%ld %d %s\n", get_time() - philo->table->star_time,
			philo->id, SLEEP);
		if (check_the_routine(philo, philo->table->time_to_sleep))
			break ;
		printf("%ld %d %s\n", get_time() - philo->table->star_time,
			philo->id, THINK);
		philo->must_eat--;
	}
}

void	*die_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->first_fork]);
	printf("%ld %d %s\n", get_time() - philo->table->star_time,
		philo->id, FORK);
	while (1)
	{
		if (get_time() - philo->last_time_eat > philo->table->time_to_die)
		{
			printf("%ld %d %s\n", get_time() - philo->table->star_time,
				philo->id, DIED);
			break ;
		}
	}
	return (NULL);
}

void	*application(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->philo_nbr == 1)
	{
		die_alone(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(200);
	handle_the_odds(philo);
	return (NULL);
}

int	start_dinner(t_table *philo)
{
	int	i;

	i = 0;
	philo->star_time = get_time();
	while (i < philo->philo_nbr)
	{
		philo->philo[i].last_time_eat = get_time();
		if (pthread_create(&philo->philo[i].thread, NULL,
				&application, &philo->philo[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < philo->philo_nbr)
	{
		if (pthread_join(philo->philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	if (philo->stop_sign == 1)
		printf("%ld %d %s\n", get_time() - philo->star_time,
			philo->id_of_the_philo_died, DIED);
	return (0);
}
