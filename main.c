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
time_t	get_time_in_ms(void)
{
	time_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
int ft_sleep(t_philo *philo, int flag)
{
	int time;
	
	time = get_time_in_ms();
	while (get_time_in_ms() - time < flag)
	{
		pthread_mutex_lock(philo->table->meal);
		if (get_time_in_ms() - philo->last_meal >= philo->table->time_to_die && philo->table->end_simulation == 0)
		{
			philo->table->end_simulation = 1;
			philo->table->id_of_the_philo_died = philo->id;
			philo->table->time_of_death = get_time_in_ms() - philo->table->star_simulation;
			pthread_mutex_unlock(philo->table->meal);
			pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
			return (1);
		}
		if (philo->table->end_simulation)
		{
			pthread_mutex_unlock(philo->table->meal);
			pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
			return (1);			
		}
		pthread_mutex_unlock(philo->table->meal);
		usleep(50);
	}
	return (0);
}
void	*ft_odd_phil(t_philo *philo)
{
	while (philo->must_eat)
	{
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->star_simulation, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->star_simulation, philo->id, "has taken a fork");
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->star_simulation, philo->id, "is eating");
		if (ft_sleep(philo, philo->table->time_to_eat))
			break ;
		philo->last_meal = get_time_in_ms();
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->star_simulation, philo->id, "is sleeping");
		if (ft_sleep(philo, philo->table->time_to_sleep))
			break ;
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->star_simulation, philo->id, "is thinking");
		philo->must_eat--;
	}
	return (NULL);
}
void	*application(void *data)
{
	t_philo *philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		usleep(100);
	ft_odd_phil(philo);
	return (NULL);
}
void	*start_dinner(t_table *philo)
{
	int i = 0;
	philo->star_simulation = get_time_in_ms();
	while (i < philo->philo_nbr)
	{
		philo->philo[i].last_meal = get_time_in_ms();
		pthread_create(&philo->philo[i].thread, NULL, &application, &philo->philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_join(philo->philo[i].thread, NULL);
		i++;
	}
	if (philo->end_simulation == 1)
		printf("%ld %d %s\n", get_time_in_ms() - philo->star_simulation, philo->id_of_the_philo_died, "died");
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
		start_dinner(&philo);
	}
}

