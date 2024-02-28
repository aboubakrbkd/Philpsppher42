/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:58:13 by aboukdid          #+#    #+#             */
/*   Updated: 2024/02/28 09:02:49 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

typedef struct s_list
{
    long num_philo;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long number_of_meals;
    struct s_list *next;
}			t_list;

void	print_error();
long	ft_atoi(char *str);
int	is_integer(char *str);
int	is_negative(char *str);
int	check_higher(char *str);
#endif
