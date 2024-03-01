/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:57:58 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/01 20:29:27 by aboukdid         ###   ########.fr       */
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

void	safe_mutex_handler(pthread_mutex_t *mutex, int flag)
{
	if (flag == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (flag == DESTROY)
		pthread_mutex_destroy(mutex);
	else if (flag == LOCK)
		pthread_mutex_lock(mutex);
	else if (flag == UNLOCK)
		pthread_mutex_unlock(mutex);
	else
		print_error();
}

void	safe_thread_handler(pthread_t *thread, void *(*foo)(void *), void *data, int flag)
{
	if (flag == CREAT)
		pthread_create(thread, 	NULL, foo , data);
	else if (flag == JOIN)
		pthread_join(*thread, NULL);
	else if (flag == DETACH)
		pthread_detach(*thread);
	else
		print_error();
}

void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[position];
		philo->left_fork = &forks[(position + 1) % philo->table->philo_nbr];
	}
	else
	{
		philo->left_fork = &forks[position];
		philo->right_fork = &forks[(position + 1) % philo->table->philo_nbr];
	}
}
void	philo_init(t_table *philos)
{
	int i = 0;
	t_philo *philo;
	while (i < philos->philo_nbr)
	{
		philo = philos->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meal_counter = 0;
		philo->table = philos;
		/*assign forks*/
		assign_forks(philo, philos->forks, i);
		i++;
	}
}
void	*data_init(t_table *philo)
{
	int	i = 0;
	philo->end_simulation = 0;
	philo->philos = malloc(sizeof(t_philo) * philo->philo_nbr);
	if (!philo->philos)
		return (NULL);
	philo->forks = malloc(sizeof(t_fork) * philo->philo_nbr);
	if (!philo->forks)
		return (NULL);
	while (i < philo->philo_nbr)
	{
		safe_mutex_handler(&philo->forks[i].fork, INIT);
		philo->forks->fork_id = i; // debug;
		i++;
	}
	philo_init(philo);
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
		parse_argument_and_fill(argv + 1, &philo); // all_good
		data_init(&philo);
	}
}

