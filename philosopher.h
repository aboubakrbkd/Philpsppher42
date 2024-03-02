/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:58:13 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/02 16:31:06 by aboukdid         ###   ########.fr       */
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




/*data of all*/
typedef struct s_philo
{
    int         id;
    int         meal_counter;
    int         full;
    int      left_fork; // a fork is a mutex
    int      right_fork;
    time_t         last_meal_time; // to check if the philosopher has die
    pthread_t   thread_id;  // a philo is a thread;
    t_table     *table;
}               t_philo;

typedef struct s_table
{
    int     philo_nbr;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     number_of_meals;
    int     end_time;
    pthread_mutex_t  *forks;
    pthread_mutex_t *meals;
    t_philo *philos;
    int index_of_the_philo_who_died;
    time_t time_of_death;
    time_t  start_time;
}               t_table;

/*data of the philosophers*/


void	print_error();
long	ft_atoi(char *str);
int	    is_integer(char *str);
int	    is_negative(char *str);
int	    check_higher(char *str);
#endif
