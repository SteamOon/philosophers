# Philosophers

This repository contains a C implementation of the dining philosophers problem using threads and mutexes, where each philosopher alternates between thinking, eating, and sleeping.

## Build

From the project root, compile the program with:

```sh
make
```

This generates the executable `./philo`.

Useful cleanup targets:

```sh
make clean
make fclean
make re
```

## Usage

Run the program with:

```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

All times are expressed in milliseconds.

### Example

```sh
./philo 5 800 200 200
./philo 5 800 200 200 7
```

## Arguments

- `number_of_philosophers`: the number of philosophers and forks
- `time_to_die`: how long a philosopher can survive without eating before dying
- `time_to_eat`: time needed to eat
- `time_to_sleep`: time needed to sleep
- `number_of_times_each_philosopher_must_eat` (optional): stops the simulation once every philosopher has eaten that many times

## Behavior

The program prints the state of each philosopher during the simulation and stops when:

- a philosopher dies, or
- the optional meal target has been reached for every philosopher

## Notes

- The implementation uses `pthread` and mutexes.
- All numeric values must be positive integers.
