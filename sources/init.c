/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:53:54 by smoon             #+#    #+#             */
/*   Updated: 2025/05/28 12:01:31 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_forks(int **fork_arr, int num, pthread_mutex_t *mutex_arr)
{
	int	i;

	*fork_arr = malloc((num) * sizeof(int));
	if (!*fork_arr)
	{
		uninit_mutex(mutex_arr, num);
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

static int	init_philos(t_data *data, t_philo **philo_arr)
{
	int	i;

	i = 0;
	while (i < data->args->philo_num)
	{
		philo_arr[i]->num = i + 1;
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
		i++;
	}
	philo_arr[i] = NULL;
	return (0);
}

static int	malloc_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->philo_num)
	{
		data->philo_arr[i] = malloc(sizeof(**data->philo_arr));
		if (!data->philo_arr[i])
		{
			free(data->forks);
			free_philos(data->philo_arr, i - 1);
			uninit_mutex(data->mutex_arr, data->args->philo_num);
			return (malloc_error());
		}
		i++;
	}
	return (0);
}

int	allocate_philos(t_data *data)
{
	t_philo	**philo_arr;

	philo_arr = malloc((data->args->philo_num + 1) * (sizeof(*philo_arr)));
	if (!philo_arr)
	{
		free(data->forks);
		uninit_mutex(data->mutex_arr, data->args->philo_num);
		return (malloc_error());
	}
	data->philo_arr = philo_arr;
	malloc_philos(data);
	init_philos(data, philo_arr);
	return (0);
}
