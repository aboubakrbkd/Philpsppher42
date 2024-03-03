/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:57:58 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/03 16:46:53 by aboukdid         ###   ########.fr       */
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
		philo->number_of_meals = -1;
	philo->time_of_death = 0;
	philo->id_of_the_philo_died = 0;
}

int initialize_philos(t_table *philo)
{
	int i = 0;
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
int initialize_forks_mutexex(t_table *philo)
{
	int i = 0;
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
	time_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_just_unlock(t_philo *philo)
{
	pthread_mutex_unlock(philo->table->meal);
	pthread_mutex_unlock(&philo->table->forks[philo->second_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->first_fork]);
}

int ft_sleep(t_philo *philo, int time)
{
	long now;
	now = get_time();
	while (get_time() - now < time)
	{
		pthread_mutex_lock(philo->table->meal);
		if (get_time() - philo->last_time_eat >= philo->table->time_to_die && philo->table->stop_sign == 0)
		{
			philo->table->stop_sign = 1;
			philo->table->id_of_the_philo_died = philo->id;
			philo->table->time_of_death = get_time() - philo->table->star_time;
			return (ft_just_unlock(philo), 1);
		}
		if (philo->table->stop_sign)
			return (ft_just_unlock(philo), 1);
		pthread_mutex_unlock(philo->table->meal);
		usleep(100);
	}
	return (0);
}
void	ft_odd_phil(t_philo *philo)
{
	while (philo->must_eat)
	{
		pthread_mutex_lock(&philo->table->forks[philo->first_fork]);
		printf("%ld %d %s\n", get_time() - philo->table->star_time, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->second_fork]);
		printf("%ld %d %s\n", get_time() - philo->table->star_time, philo->id, "has taken a fork");
		printf("%ld %d %s\n", get_time() - philo->table->star_time, philo->id, "is_eating");
		if (ft_sleep(philo, philo->table->time_to_eat))
			break ;
		philo->last_time_eat = get_time();
		pthread_mutex_unlock(&philo->table->forks[philo->first_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->second_fork]);
		printf("%ld %d %s\n", get_time() - philo->table->star_time, philo->id, "is_sleeping");
		if (ft_sleep(philo, philo->table->time_to_sleep))
			break ;
		printf("%ld %d %s\n", get_time() - philo->table->star_time, philo->id, "is_thinking");
		philo->must_eat--;
	}
}
void *application(void *data)
{
	t_philo *philo = (t_philo*)data;
	
	if (philo->id % 2 == 0)
		usleep(200);
	ft_odd_phil(philo);
	return (NULL);
}
int start_l3cha(t_table *philo)
{
	int i = 0;
	philo->star_time = get_time();
	while (i < philo->philo_nbr)
	{
		philo->philo[i].last_time_eat = get_time();
		pthread_create(&philo->philo[i].thread, NULL, &application, &philo->philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_join(philo->philo[i].thread, NULL);
		i++;
	}
	if (philo->stop_sign == 1)
		printf("%ld %d %s\n", get_time() - philo->star_time, philo->id_of_the_philo_died, "died");
	return (0);
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
		start_l3cha(&philo);
	}
}

