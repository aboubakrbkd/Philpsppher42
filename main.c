/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:57:58 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/04 16:06:20 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	parse_argument_and_fill(char **argv, t_table *philo)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (is_integer(argv[i]) || check_higher(argv[i])
			|| is_negative(argv[i]))
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
		philo->number_of_meals = -1;
}

void	unlock_mutexes(t_philo *philo)
{
	pthread_mutex_unlock(philo->table->meal);
	pthread_mutex_unlock(&philo->table->forks[philo->second_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->first_fork]);
}

int	check_the_routine(t_philo *philo, int time)
{
	long	now;

	now = get_time();
	while (get_time() - now < time)
	{
		pthread_mutex_lock(philo->table->meal);
		if (get_time() - philo->last_time_eat >= philo->table->time_to_die
			&& !philo->table->stop_sign)
		{
			philo->table->stop_sign = 1;
			philo->table->id_of_the_philo_died = philo->id;
			philo->table->time_of_death = get_time() - philo->table->star_time;
			unlock_mutexes(philo);
			return (1);
		}
		if (philo->table->stop_sign)
		{
			unlock_mutexes(philo);
			return (1);
		}
		pthread_mutex_unlock(philo->table->meal);
		usleep(100);
	}
	return (0);
}

void	*clean_all(t_table *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_mutex_destroy(&(philo->forks[i]));
		i++;
	}
	pthread_mutex_destroy(philo->meal);
	free(philo->forks);
	free(philo->philo);
	free(philo->meal);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table	philo;

	if (argc != 5 && argc != 6)
		print_error();
	else
	{
		parse_argument_and_fill(argv + 1, &philo);
		initialize_data(&philo);
		if (start_dinner(&philo) == 1)
		{
			printf("Error creating the threads\n");
			return (1);
		}
		clean_all(&philo);
	}
	return (0);
}
