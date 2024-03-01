/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:58:13 by aboukdid          #+#    #+#             */
/*   Updated: 2024/02/29 14:18:52 by aboukdid         ###   ########.fr       */
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
/* data of the forks*/
typedef struct s_fork
{
    pthread_mutex_t fork;
    int fork_id;
}               t_fork;

/*data of all*/
typedef struct s_philo
{
    int id;
    int meal_counter;
    int full;
    int last_meal_time; // to check if the philosopher has die
    t_fork *left_fork; // a fork is a mutex
    t_fork *right_fork;
    pthread_t thread_id;  // a philo is a thread;
    t_table *table;
}               t_philo;

typedef struct s_table
{
    int philo_nbr; // argv[1]
    int time_to_die; // argv[2]
    int time_to_eat; // argv[3]
    int time_to_sleep; // argv[4]
    int number_of_meals; // argv[5]
    int start_simulation; // i can delete it in the end
    int end_simulation; // i can delete it in the end
    t_fork *forks; // to initialize to all the forks
    t_philo *philos; // to initialize the philosophers
}               t_table;

/*data of the philosophers*/





void	print_error();
long	ft_atoi(char *str);
int	is_integer(char *str);
int	is_negative(char *str);
int	check_higher(char *str);
#endif
