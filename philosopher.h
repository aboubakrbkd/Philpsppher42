/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:58:13 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/02 20:07:16 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h> 


#define INIT 0
#define DESTROY 1
#define LOCK 2
#define UNLOCK 3
#define CREAT 4
#define JOIN 5 
#define DETACH 6


typedef struct s_table	t_table;


typedef struct s_philo
{
    int time_to_eat;
    int id;
    int left_fork;
    int right_fork;
    time_t last_meal;
    pthread_t thread;
    int must_eat;
    t_table *table;
}               t_philo;

typedef struct s_table
{
    time_t time_of_death;
    int id_of_the_philo_died;
    int philo_nbr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_meals;
    time_t star_simulation;
    int end_simulation;
    int max_ate;
    t_philo *philo;
    pthread_mutex_t *forks;
    pthread_mutex_t *log;
    pthread_mutex_t *meal;
}               t_table;

/*data of the philosophers*/


void	print_error();
long	ft_atoi(char *str);
int	    is_integer(char *str);
int	    is_negative(char *str);
int	    check_higher(char *str);
#endif
