/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:28:05 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/05 15:59:29 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo/philosopher.h"
#include <semaphore.h>

#define THREAD_NUM 4
int x = 0;
sem_t semaphore;
void *routine()
{
	printf("hello from thread \n");
	return (NULL);
}
int main(int argc, char **argv)
{
	pthread_t th[THREAD_NUM];
	sem_init(&semaphore, 0, 1);
	int i; 
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("error");
	}
	
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("error");
	}
	printf("%d\n", x);
	sem_destroy(&semaphore);
}