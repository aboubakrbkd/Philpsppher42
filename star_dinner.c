/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:50:15 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/04 13:50:24 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_odd_phil(t_philo *philo)
{
	while (philo->must_eat)
	{
		pthread_mutex_lock(&philo->table->forks[philo->first_fork]);
		printf("%ld %d %s\n", get_time() - philo->table->star_time,
			philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->second_fork]);
		printf("%ld %d %s\n", get_time() - philo->table->star_time,
			philo->id, "has taken a fork");
		printf("%ld %d %s\n", get_time() - philo->table->star_time,
			philo->id, "is eating");
		if (ft_sleep(philo, philo->table->time_to_eat))
			break ;
		philo->last_time_eat = get_time();
		pthread_mutex_unlock(&philo->table->forks[philo->first_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->second_fork]);
		printf("%ld %d %s\n", get_time() - philo->table->star_time,
			philo->id, "is sleeping");
		if (ft_sleep(philo, philo->table->time_to_sleep))
			break ;
		printf("%ld %d %s\n", get_time() - philo->table->star_time,
			philo->id, "is thinking");
		philo->must_eat--;
	}
}

void	*die_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->first_fork]);
	printf("%ld %d %s\n", get_time() - philo->table->star_time,
		philo->id, "is taking a fork");
	while (1)
	{
		if (get_time() - philo->last_time_eat > philo->table->time_to_die)
		{
			printf("%ld %d %s\n", get_time() - philo->table->star_time,
				philo->id, "died");
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
	ft_odd_phil(philo);
	return (NULL);
}

int	start_l3cha(t_table *philo)
{
	int	i;

	i = 0;
	philo->star_time = get_time();
	while (i < philo->philo_nbr)
	{
		philo->philo[i].last_time_eat = get_time();
		pthread_create(&philo->philo[i].thread, NULL,
			&application, &philo->philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_join(philo->philo[i].thread, NULL);
		i++;
	}
	if (philo->stop_sign == 1)
		printf("%ld %d %s\n", get_time() - philo->star_time,
			philo->id_of_the_philo_died, "died");
	return (0);
}
