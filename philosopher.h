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

// typedef struct s_list
// {
//     long num_philo;
//     long time_to_die;
//     long time_to_eat;
//     long time_to_sleep;
//     long number_of_meals;
//     struct s_list *next;
// }			t_list;

typedef struct s_fork
{
    pthread_mutex_t fork;
    int fork_id;

}               t_fork;

typedef struct s_philo
{
    int id;//the id of the philo;
    int meals_counter;//is the argv[5];
    int full;//to check if he eats the max meals_counter or not;
    int last_meal_time;//time past from last meal;
    t_fork *left_fork;
    t_fork *right_fork;
    pthread_t thread_id;
}               t_philo;
typedef struct s_table
{
    int philo_nbr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_meals;
    int start_simulation;
    int end_simulation;
    t_fork *forks;
    t_philo *philos;
}               t_table;




void	print_error();
long	ft_atoi(char *str);
int	is_integer(char *str);
int	is_negative(char *str);
int	check_higher(char *str);
#endif
