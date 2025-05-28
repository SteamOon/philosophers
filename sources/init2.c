/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:43:03 by smoon             #+#    #+#             */
/*   Updated: 2025/05/28 10:44:18 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*init_mutex(int num)
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
			uninit_mutex(mutex_arr, i);
			return (pthread_error("initialising mutexes"), NULL);
		}
		i++;
	}
	return (mutex_arr);
}
