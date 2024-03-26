/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:58:13 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/26 00:43:17 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef struct s_table	t_table;
typedef struct s_philo
{
	int			times_ate;
	int			id;
	int			first_fork;
	int			second_fork;
	time_t		last_time_eat;
	pthread_t	thread;
	int			must_eat;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	time_t			time_of_death;
	int				id_of_the_philo_died;
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	time_t			star_time;
	int				stop_sign;
	int				max_ate;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*meal;
}				t_table;

int		print_error(void);
long	ft_atoi(char *str);
int		is_integer(char *str);
int		is_negative(char *str);
int		check_higher(char *str);
int		initialize_philos(t_table *philo);
int		initialize_forks_mutexex(t_table *philo);
void	*initialize_data(t_table *philo);
time_t	get_time(void);
int		start_dinner(t_table *philo);
void	*application(void *data);
void	*die_alone(t_philo *philo);
void	handle_the_odds(t_philo *philo);
int		check_the_routine(t_philo *philo, int time);
void	*clean_all(t_table *philo);
#endif
