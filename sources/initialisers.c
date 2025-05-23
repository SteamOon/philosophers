/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:53:54 by smoon             #+#    #+#             */
/*   Updated: 2025/05/23 12:17:59 by smoon            ###   ########.fr       */
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

static int	initialise_philos(t_data *data, t_philo **philo_arr)
{
	int	i;

	i = 0;
	while (i < data->args->philo_num)
	{
		philo_arr[i]->num = i + 1;
		philo_arr[i]->eat_count = 0;
		philo_arr[i]->left_fork = &data->forks[i];
		philo_arr[i]->left_mutex = &data->mutex_arr[i];
		if (i == data->args->philo_num - 1)
		{
			philo_arr[i]->right_fork = &data->forks[0];
			philo_arr[i]->right_mutex = &data->mutex_arr[0];
		}
		else
		{
			philo_arr[i]->right_fork = &data->forks[i + 1];
			philo_arr[i]->right_mutex = &data->mutex_arr[i + 1];
		}
		philo_arr[i]->args = data->args;
		pthread_mutex_init(&philo_arr[i]->eat_time_mutex, NULL);
		pthread_mutex_init(&philo_arr[i]->eat_count_mutex, NULL);
		philo_arr[i]->last_meal = cur_time(data->args->start_time);
		printf("Philo %d create time: %d\n", philo_arr[i]->num, philo_arr[i]->last_meal);
		i++;
	}
	philo_arr[i] = NULL;
	return (0);
}

int	allocate_philos(t_data *data)
{
	int	i;
	t_philo **philo_arr;

	i = 0;
	philo_arr = malloc((data->args->philo_num + 1) * (sizeof(*philo_arr)));
	// printf("%p allocated\n", &philo_arr);
	if (!philo_arr)
	{
		free(data->forks);
		uninitialise_mutex(data->mutex_arr, data->args->philo_num);
		return (malloc_error());
	}
	while (i < data->args->philo_num)
	{
		philo_arr[i] = malloc(sizeof(**philo_arr));
		// printf("%p allocated\n", &philo_arr[i]);
		if (!philo_arr[i])
		{
			free(data->forks);
			free_philos(philo_arr, i - 1);
			uninitialise_mutex(data->mutex_arr, data->args->philo_num);
			return (malloc_error());
		}
		i++;
	}
	initialise_philos(data, philo_arr);
	data->philo_arr = philo_arr;
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
