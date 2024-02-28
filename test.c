#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
    ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]

    even:
        time_to_die = time_to_eat + time_to_sleep + 10;
    odd:
        time_to_die = time_to_eat * 2 + time_to_sleep + 10;
    ways i can prevent from deadlock {
        1) odd sleep(time_to_eat / 2)
        2) odd start taking from right fork, even start taking from left fork
        3) all philosophers take from right fork, except for the last one.
    }
*/

int x = 0;

void	*routine()
{
	for(int i = 0; i < 10; i++)
		x++;
    //pthread_self();
    printf("%d\n", pthread_self());
    printf("thr id of the thread function is %d and for the parent id %d\n", getpid(), getppid());
    return(0);
}

int main(int argc, char **argv)
{
	pthread_t t1;
	pthread_t t2;
	if (pthread_create(&t1, NULL, &routine, NULL))
		return(1);
	if (pthread_create(&t2, NULL, &routine, NULL))
		return(1);
	if (pthread_join(t1, NULL))
		return (1);
	if (pthread_join(t2, NULL)) 
		return (1);
    printf("thr id of the main function is %d and for the parent id %d\n", getpid(), getppid());
	printf("the value of x is: %d\n", x);
    if (pthread_equal(t1, t2) == 0)
        printf("not equal\n");
    else
        printf("euqal\n");
}

