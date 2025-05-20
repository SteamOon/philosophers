/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:52:04 by smoon             #+#    #+#             */
/*   Updated: 2025/05/20 17:09:12 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*even_eating(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo->left_mutex);
	printf("%ld %d has taken a fork\n", msecs_now(), philo->num);
	pthread_mutex_lock(philo->right_mutex);
	printf("%ld %d has taken a fork\n", msecs_now(), philo->num);
	printf("%ld %d is eating\n", msecs_now(), philo->num);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_mutex);
	pthread_mutex_unlock(philo->right_mutex);
	printf("%ld %d is sleeping\n", msecs_now(), philo->num);
	usleep(philo->time_to_sleep);
	printf("%ld %d is thinking\n", msecs_now(), philo->num);
	return (NULL);
}

void	*odd_eating(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	printf("%ld %d is thinking\n", msecs_now(), philo->num);
	usleep(philo->time_to_sleep); //change to time to think***********
	pthread_mutex_lock(philo->right_mutex);
	printf("%ld %d has taken a fork\n", msecs_now(), philo->num);
	pthread_mutex_lock(philo->left_mutex);
	printf("%ld %d has taken a fork\n", msecs_now(), philo->num);
	printf("%ld %d is eating\n", msecs_now(), philo->num);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->right_mutex);
	pthread_mutex_unlock(philo->left_mutex);
	printf("%ld %d is sleeping\n", msecs_now(), philo->num);
	usleep(philo->time_to_sleep);
	return (NULL);
}
/*

using array and i
void	*even_eating(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->mutex_arr[philo->num - 1]);
	printf("%ld %d has taken a fork\n", msecs_now(), philo->num);
	pthread_mutex_lock(&philo->mutex_arr[philo->num]);
	printf("%ld %d has taken a fork\n", msecs_now(), philo->num);
	printf("%ld %d is eating\n", msecs_now(), philo->num);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->mutex_arr[philo->num - 1]);
	pthread_mutex_unlock(&philo->mutex_arr[philo->num]);
	printf("%ld %d is sleeping\n", msecs_now(), philo->num);
	usleep(philo->time_to_sleep);
	printf("%ld %d is thinking\n", msecs_now(), philo->num);
	return (NULL);
}

void	*odd_eating(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	printf("%ld %d is thinking\n", msecs_now(), philo->num);
	usleep(philo->time_to_sleep); //change to time to think***********
	pthread_mutex_lock(&philo->mutex_arr[philo->num]);
	printf("%ld %d has taken a fork\n", msecs_now(), philo->num);
	pthread_mutex_lock(&philo->mutex_arr[philo->num - 1]);
	printf("%ld %d has taken a fork\n", msecs_now(), philo->num);
	printf("%ld %d is eating\n", msecs_now(), philo->num);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->mutex_arr[philo->num]);
	pthread_mutex_unlock(&philo->mutex_arr[philo->num - 1]);
	printf("%ld %d is sleeping\n", msecs_now(), philo->num);
	usleep(philo->time_to_sleep);
	return (NULL);
}
*/
