/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:53:54 by smoon             #+#    #+#             */
/*   Updated: 2025/05/20 17:31:07 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*initialise_mutex(int num)
{
	int				i;
	pthread_mutex_t *mutex_arr;

	i = 0;
	mutex_arr = malloc(num * sizeof(pthread_mutex_t));
	// printf("%p allocated\n", &mutex_arr);
	if (!mutex_arr)
		return (malloc_error(), NULL);
	while (i < num)
	{
		if (pthread_mutex_init(&mutex_arr[i], NULL) == -1)
		{
			uninitialise_mutex(mutex_arr, i);
			return (pthread_error("initialising mutexes"), NULL);
		}
		i++;
	}
	return (mutex_arr);
}

int	initialise_forks(int **fork_arr, int num, pthread_mutex_t *mutex_arr)
{
	int	i;

	*fork_arr = malloc((num) * sizeof(int));
	// printf("%p allocated\n", &fork_arr);
	if (!*fork_arr)
	{
		uninitialise_mutex(mutex_arr, num);
		return (malloc_error());
	}
	i = 0;
	while (i < num)
	{
		(*fork_arr)[i] = i;
		i++;
	}
	return (0);
}


static int	initialise_philos(t_args *args, t_philo **philo_arr)
{
	int	i;

	i = 0;
	while (i < args->philo_num)
	{
		philo_arr[i]->num = i + 1;
		gettimeofday(&philo_arr[i]->time_last_ate, NULL);
		philo_arr[i]->left_fork = &args->forks[i];
		philo_arr[i]->left_mutex = &args->mutex_arr[i];
		if (i == args->philo_num - 1)
		{
			philo_arr[i]->right_fork = &args->forks[0];
			philo_arr[i]->right_mutex = &args->mutex_arr[0];
		}
		else
		{
			philo_arr[i]->right_fork = &args->forks[i + 1];
			philo_arr[i]->right_mutex = &args->mutex_arr[i + 1];
		}
		philo_arr[i]->time_to_die = args->time_to_die;
		philo_arr[i]->time_to_eat = args->time_to_eat;
		philo_arr[i]->time_to_sleep = args->time_to_sleep;
		philo_arr[i]->mutex_arr = args->mutex_arr;
		printf("Philo %d create time: %ld%06ld\n", philo_arr[i]->num, philo_arr[i]->time_last_ate.tv_sec, philo_arr[i]->time_last_ate.tv_usec);
		i++;
	}
	philo_arr[i] = NULL;
	return (0);
}

int	allocate_philos(t_args *args)
{
	int	i;
	t_philo **philo_arr;

	i = 0;
	philo_arr = malloc((args->philo_num + 1) * (sizeof(*philo_arr)));
	// printf("%p allocated\n", &philo_arr);
	if (!philo_arr)
	{
		free(args->forks);
		uninitialise_mutex(args->mutex_arr, args->philo_num);
		return (malloc_error());
	}
	while (i < args->philo_num)
	{
		philo_arr[i] = malloc(sizeof(**philo_arr));
		// printf("%p allocated\n", &philo_arr[i]);
		if (!philo_arr[i])
		{
			free(args->forks);
			free_philos(philo_arr, i - 1);
			uninitialise_mutex(args->mutex_arr, args->philo_num);
			return (malloc_error());
		}
		i++;
	}
	initialise_philos(args, philo_arr);
	args->philo_arr = philo_arr;
	return (0);
}

int	initialise_even_threads(pthread_t **thread_arr, t_philo **philo_arr, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_create(&(*thread_arr)[i], NULL, &even_eating, philo_arr[i]) != 0)
			return (1);
		i += 2;
	}
	return (0);
}

int	initialise_odd_threads(pthread_t **thread_arr, t_philo **philo_arr, int num)
{
	int	i;

	i = 1;
	while (i < num)
	{
		if (pthread_create(&(*thread_arr)[i], NULL, &odd_eating, philo_arr[i]) != 0)
			return (1);
		i += 2;
	}
	return (0);
}
