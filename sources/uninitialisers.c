/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uninitialisers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:05:07 by smoon             #+#    #+#             */
/*   Updated: 2025/05/23 12:17:59 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	uninitialise_mutex(pthread_mutex_t *mutex_arr, int num)
{
	num = num - 1;
	while (num >= 0)
	{
		pthread_mutex_destroy(&mutex_arr[num]);
		num--;
	}
	free(mutex_arr);
	// printf("%p freed\n", &mutex_arr);
	return (1);
}

int	free_philos(t_philo **philo_arr, int num)
{
	num--;
	while (num >= 0)
	{

		pthread_mutex_destroy(&philo_arr[num]->eat_time_mutex);
		pthread_mutex_destroy(&philo_arr[num]->eat_count_mutex);
		free(philo_arr[num]);
		// printf("%p freed\n", &philo_arr[num]);
		num--;
	}
	free(philo_arr);
	// printf("%p freed\n", &philo_arr);
	return (0);
}

int	join_even_threads(pthread_t **thread_arr, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_join((*thread_arr)[i], NULL) != 0)
			return (1);
		i += 2;
	}
	return (0);
}

int	join_odd_threads(pthread_t **thread_arr, int num)
{
	int	i;

	i = 1;
	while (i < num)
	{
		if (pthread_join((*thread_arr)[i], NULL) != 0)
			return (1);
		i += 2;
	}
	return (0);
}
