/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:57:58 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/02 16:40:58 by aboukdid         ###   ########.fr       */
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
		philo->right_fork = i;
		philo->left_fork = (i + 1) % philo->table->philo_nbr; 
		i++;
	}
}

void	*data_init(t_table *philo)
{
	int	i = 0;
	philo->end_time = 0;
	philo->philos = malloc(sizeof(t_philo) * philo->philo_nbr);
	if (!philo->philos)
		return (NULL);
	philo->forks = malloc(sizeof(t_table) * philo->philo_nbr);
	if (!philo->forks)
		return (NULL);
	philo->meals = malloc(sizeof(t_table) * philo->philo_nbr);
	if (!philo->meals)
		return (NULL);
	while (i < philo->philo_nbr)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	philo_init(philo);
	return (NULL);
}

time_t	get_time_in_ms(void)
{
	time_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
int	ft_sleep(t_philo *philo, int flag)
{
	time_t time = get_time_in_ms();
	while (get_time_in_ms() - time < flag)
	{
		pthread_mutex_lock(philo->table->meals);
		if (get_time_in_ms() - philo->last_meal_time >= philo->table->time_to_die && !philo->table->end_time)
		{
			philo->table->end_time = 1;
			philo->table->index_of_the_philo_who_died = philo->id;
			philo->table->time_of_death = get_time_in_ms() - philo->table->start_time;
			pthread_mutex_unlock(philo->table->meals);
			pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
			return (1) ;
		}
		if (philo->table->end_time)
		{
			pthread_mutex_unlock(philo->table->meals);
			pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
			return (1) ;
		}
		pthread_mutex_unlock(philo->table->meals);
		usleep(100);
	}
	return (0);
}
void	ft_odd_phill(t_philo *philo)
{
	printf("%d\n", philo->meal_counter);
	while (philo->table->number_of_meals)
	{
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id, "has taken a fork");
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id, "is eating");
		if (ft_sleep(philo, philo->table->time_to_eat))
			break ;
		philo->last_meal_time = get_time_in_ms();
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id, "is sleeping");
		if (ft_sleep(philo, philo->table->time_to_sleep))
			break ;
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id, "is thinking");
		philo->meal_counter--;
	}
}
void	*application(void	*data)
{
	t_philo *philo = (t_philo *)data;
	// if (philo->table->philo_nbr == 1)
	// 	to_do()
	if (philo->id % 2 == 0)
		usleep(50);
	ft_odd_phill(philo);
	return (NULL);
}

void	dinner(t_table *philo)
{
	int i = 0;
	philo->start_time = get_time_in_ms();
	while (i < philo->philo_nbr)
	{
		philo->philos[i].last_meal_time = get_time_in_ms();
		pthread_create(&philo->philos[i].thread_id, NULL, &application, &philo->philos[i]);
		i++;
	}
	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_join(philo->philos[i].thread_id, NULL);
		i++;
	}
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
		data_init(&philo);
		dinner(&philo);
	}
}

