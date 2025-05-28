/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:23:03 by smoon             #+#    #+#             */
/*   Updated: 2025/05/28 11:55:17 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat_print(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->args->printf_mutex);
	time = cur_time(philo->args->start_time);
	printf("%d %d is eating\n", time, philo->num);
	pthread_mutex_unlock(&philo->args->printf_mutex);
	return (time);
}

int	fork_print(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->args->printf_mutex);
	time = cur_time(philo->args->start_time);
	printf("%d %d has taken a fork\n", time, philo->num);
	pthread_mutex_unlock(&philo->args->printf_mutex);
	return (time);
}

int	sleep_print(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->args->printf_mutex);
	time = cur_time(philo->args->start_time);
	printf("%d %d is sleeping\n", time, philo->num);
	pthread_mutex_unlock(&philo->args->printf_mutex);
	return (time);
}

int	think_print(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->args->printf_mutex);
	time = cur_time(philo->args->start_time);
	printf("%d %d is thinking\n", time, philo->num);
	pthread_mutex_unlock(&philo->args->printf_mutex);
	return (time);
}

int	died_print(int time, int num, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%d %d died\n", time, num);
	pthread_mutex_unlock(mutex);
	return (time);
}
