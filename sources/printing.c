/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:23:03 by smoon             #+#    #+#             */
/*   Updated: 2025/05/27 14:04:56 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat_print(long start_time, int num, pthread_mutex_t *mutex)
{
	int	time;

	pthread_mutex_lock(mutex);
	time = cur_time(start_time);
	printf("%d %d is eating\n", time, num);
	pthread_mutex_unlock(mutex);
	return (time);
}

int	fork_print(long start_time, int num, pthread_mutex_t *mutex)
{
	int	time;

	pthread_mutex_lock(mutex);
	time = cur_time(start_time);
	printf("%d %d has taken a fork\n", time, num);
	pthread_mutex_unlock(mutex);
	return (time);
}

int	sleep_print(long start_time, int num, pthread_mutex_t *mutex)
{
	int	time;

	pthread_mutex_lock(mutex);
	time = cur_time(start_time);
	printf("%d %d is sleeping\n", time, num);
	pthread_mutex_unlock(mutex);
	return (time);
}

int	think_print(long start_time, int num, pthread_mutex_t *mutex)
{
	int	time;

	pthread_mutex_lock(mutex);
	time = cur_time(start_time);
	printf("%d %d is thinking\n", time, num);
	pthread_mutex_unlock(mutex);
	return (time);
}

int	died_print(int time, int num, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	// time = cur_time(start_time);
	printf("%d %d died\n", time, num);
	pthread_mutex_unlock(mutex);
	return (time);
}
