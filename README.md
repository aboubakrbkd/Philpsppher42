# Philosophers

A multi-threaded simulation of the classic Dining Philosophers problem in C.

## Overview

This project simulates philosophers sitting at a table, alternating between thinking, eating, and sleeping. Each philosopher needs two forks to eat, and synchronization is handled using mutexes to prevent deadlocks.

## Building

```sh
make
```

## Running

```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```

**Arguments:**
- `number_of_philosophers`: Number of philosophers at the table
- `time_to_die`: Time (ms) before a philosopher dies from hunger
- `time_to_eat`: Time (ms) to eat
- `time_to_sleep`: Time (ms) to sleep
- `number_of_meals`: (Optional) Number of times each philosopher must eat before exiting

## Example

```sh
./philo 5 800 200 200 10
```

This simulates 5 philosophers where each must eat 10 times before the simulation ends.

## Cleanup

```sh
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild from scratch
```
