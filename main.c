/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:57:58 by aboukdid          #+#    #+#             */
/*   Updated: 2024/02/29 17:15:35 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	parse_argument_and_fill(char **argv, int argc, t_table *philo)
{
	int i = 0;
	while (argv[i])
	{
		if (is_integer(argv[i]) || check_higher(argv[i]) || is_negative(argv[i]))
			print_error();
		i++;
	}
	philo->philo_nbr = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->number_of_meals = ft_atoi(argv[5]);
	else
		philo->number_of_meals = 0;
}


void	safe_mutex_unlock(pthread_mutex_t *mutex, int flag)
{
	if (flag == 1)
		pthread_mutex_lock(mutex);
	else if (flag == 0)
		pthread_mutex_unlock(mutex);
	else if (flag == 2)
		pthread_mutex_init(mutex, NULL);
	else if (flag == 3)
		pthread_mutex_destroy(mutex);
}

void	safe_thread(pthread_t *thread, void *(*foo)(void *), void	*data, int flag)
{
	if(flag == 0)
		pthread_create(thread, NULL, foo, data);
	else if (flag == 1)
		pthread_join(*thread, NULL);
	else if (flag == 2)
		pthread_detach(*thread);
}

void	philo_init(t_table *philo)
{
	int i = 0;
	t_philo *philos;
	while (i < philo->philo_nbr)
	{
		philos = philo->philos + i;
		philos->id = i + 1;
		philos->full = 0;
		philos->meals_counter = 0;
		philos->
		
	}
}
void	data_init(t_table *philo)
{
	int i = 0;
	philo->end_simulation = 0;
	philo->philos = malloc(sizeof(t_table) * philo->philo_nbr);
	if (!philo->philos)
		return(NULL);
	philo->forks = malloc(sizeof(t_table) * philo->philo_nbr);
	if (!philo->forks)
		return (NULL);
	while (i < philo->philo_nbr)
	{
		safe_mutex_unlock(&philo->forks[i].fork, 2);
		philo->forks[i].fork_id = i; // debug;	
	}
	phill_init(philo);
	
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
		parse_argument_and_fill(argv + 1, argc, &philo);
		data_init(&philo);
	}
}

