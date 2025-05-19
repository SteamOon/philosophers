/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:53:54 by smoon             #+#    #+#             */
/*   Updated: 2025/05/19 16:54:00 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*initialise_mutex(int num)
{
	int				i;
	pthread_mutex_t *mutex_arr;

	i = 0;
	mutex_arr = malloc(num * sizeof(pthread_mutex_t));
	printf("%p allocated\n", &mutex_arr);
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

	*fork_arr = malloc((num + 1) * sizeof(int));
	printf("%p allocated\n", &fork_arr);
	if (!*fork_arr)
	{
		uninitialise_mutex(mutex_arr, num);
		return (malloc_error());
	}
	i = 0;
	while (i <= num)
	{
		(*fork_arr)[i] = 0;
		i++;
	}
	return (0);
}


static int	initialise_philos(t_philo **philo_arr, int *forks, int num)
{
	int	i;

	i = 0;
	philo_arr[i]->num = i;
	philo_arr[i]->left_fork = NULL;
	philo_arr[i]->right_fork = NULL;
	i++;
	philo_arr[i]->num = i;
	philo_arr[i]->left_fork = &forks[num];
	philo_arr[i]->right_fork = &forks[i];
	i++;
	while (i <= num)
	{
		philo_arr[i]->num = i;
		philo_arr[i]->left_fork = &forks[i - 1];
		philo_arr[i]->right_fork = &forks[i];
		i++;
	}
	philo_arr[i] = NULL;
	return (0);
}

t_philo	**allocate_philos(int *forks, int num, pthread_mutex_t *mutex_arr)
{
	int	i;
	t_philo **philo_arr;

	i = 0;
	philo_arr = malloc((num + 2) * (sizeof(*philo_arr)));
	printf("%p allocated\n", &philo_arr);
	if (!philo_arr)
	{
		free(forks);
		uninitialise_mutex(mutex_arr, num);
		return (malloc_error(), NULL);
	}
	while (i <= num)
	{
		philo_arr[i] = malloc(sizeof(**philo_arr));
		printf("%p allocated\n", &philo_arr[i]);
		if (!philo_arr[i])
		{
			free(forks);
			free_philos(philo_arr, i - 1);
			uninitialise_mutex(mutex_arr, num);
			return (malloc_error(), NULL);
		}
		i++;
	}
	initialise_philos(philo_arr, forks, num);
	return (philo_arr);
}

// int	initialise_threads(num)
