/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uninitialisers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:05:07 by smoon             #+#    #+#             */
/*   Updated: 2025/05/19 16:43:44 by smoon            ###   ########.fr       */
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
	printf("%p freed\n", &mutex_arr);
	return (1);
}

int	free_philos(t_philo **philo_arr, int num)
{
	while (num >= 0)
	{
		free(philo_arr[num]);
		printf("%p freed\n", &philo_arr[num]);
		num--;
	}
	free(philo_arr);
	printf("%p freed\n", &philo_arr);
	return (0);
}
