/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:52:04 by smoon             #+#    #+#             */
/*   Updated: 2025/05/23 15:54:59 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	update_eat_stats(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_time_mutex);
	philo->last_meal = cur_time(philo->args->start_time);
	pthread_mutex_unlock(&philo->eat_time_mutex);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	return ;
}

static int	get_sleep_time(t_philo *philo,  int old_time)
{
	int	time;

	time = philo->args->time_to_eat + philo->args->time_to_sleep + old_time - cur_time(philo->args->start_time);
	if (time < 0)
		time = 0;
	return (time);
}

static int	get_eat_time(t_philo *philo, int old_time)
{
	int	time;

	time = philo->args->time_to_eat + old_time - cur_time(philo->args->start_time);
	if (time < 0)
		time = 0;
	return (time);
}

void	*even_eating(void *ptr)
{
	t_philo			*philo;
	int				time;

	philo = (t_philo *)ptr;
	while (philo->args->eat_target == 0 || philo->eat_count	< philo->args->eat_target)
	{
		pthread_mutex_lock(philo->left_mutex);
		*philo->left_fork = philo->num;
		if (is_running(philo->args) == 0)
		{
			pthread_mutex_unlock(philo->left_mutex);
			break ;
		}
		printf("%d %d has taken a fork\n", cur_time(philo->args->start_time), philo->num);
		pthread_mutex_lock(philo->right_mutex);
		*philo->right_fork = philo->num;
		if (is_running(philo->args) == 0)
		{
			pthread_mutex_unlock(philo->right_mutex);
			pthread_mutex_unlock(philo->left_mutex);
			break ;
		}
		printf("%d %d has taken a fork\n", cur_time(philo->args->start_time), philo->num);
		time = cur_time(philo->args->start_time);
		printf("%d %d is eating\n", time, philo->num);
		update_eat_stats(philo);
		usleep(get_eat_time(philo, time));
		pthread_mutex_unlock(philo->right_mutex);
		pthread_mutex_unlock(philo->left_mutex);
		if (is_running(philo->args) == 0)
			break ;
		printf("%d %d is sleeping\n", cur_time(philo->args->start_time), philo->num);
		usleep(get_sleep_time(philo, time));
		if (is_running(philo->args) == 0)
			break ;
		printf("%d %d is thinking\n", cur_time(philo->args->start_time), philo->num);
		usleep(philo->args->time_to_think);
	}
	return (NULL);
}

void	*odd_eating(void *ptr)
{
	t_philo	*philo;
	int		time;

	philo = (t_philo *)ptr;
	while (philo->args->eat_target == 0 || philo->eat_count	< philo->args->eat_target)
	{
		if (is_running(philo->args) == 0)
			break ;
		printf("%d %d is thinking\n", cur_time(philo->args->start_time), philo->num);
		usleep(philo->args->time_to_think);
		pthread_mutex_lock(philo->right_mutex);
		*philo->right_fork = philo->num;
		if (is_running(philo->args) == 0)
		{
			pthread_mutex_unlock(philo->right_mutex);
			break ;
		}
		printf("%d %d has taken a fork\n", cur_time(philo->args->start_time), philo->num);
		pthread_mutex_lock(philo->left_mutex);
		*philo->left_fork = philo->num;
		if (is_running(philo->args) == 0)
		{
			pthread_mutex_unlock(philo->left_mutex);
			pthread_mutex_unlock(philo->right_mutex);
			break ;
		}
		printf("%d %d has taken a fork\n", cur_time(philo->args->start_time), philo->num);
		time = cur_time(philo->args->start_time);
		printf("%d %d is eating\n", time, philo->num);
		update_eat_stats(philo);
		usleep(get_eat_time(philo, time));
		pthread_mutex_unlock(philo->left_mutex);
		pthread_mutex_unlock(philo->right_mutex);
		if (is_running(philo->args) == 0)
			break ;
		printf("%d %d is sleeping\n", cur_time(philo->args->start_time), philo->num);
		usleep(get_sleep_time(philo, time));
	}
	return (NULL);
}
/*

using array and i
void	*even_eating(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->mutex_arr[philo->num - 1]);
	printf("%d %d has taken a fork\n", msecs_now(), philo->num);
	pthread_mutex_lock(&philo->mutex_arr[philo->num]);
	printf("%d %d has taken a fork\n", msecs_now(), philo->num);
	printf("%d %d is eating\n", msecs_now(), philo->num);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->mutex_arr[philo->num - 1]);
	pthread_mutex_unlock(&philo->mutex_arr[philo->num]);
	printf("%d %d is sleeping\n", msecs_now(), philo->num);
	usleep(philo->time_to_sleep);
	printf("%d %d is thinking\n", msecs_now(), philo->num);
	return (NULL);
}

void	*odd_eating(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	printf("%d %d is thinking\n", msecs_now(), philo->num);
	usleep(philo->time_to_sleep); //change to time to think***********
	pthread_mutex_lock(&philo->mutex_arr[philo->num]);
	printf("%d %d has taken a fork\n", msecs_now(), philo->num);
	pthread_mutex_lock(&philo->mutex_arr[philo->num - 1]);
	printf("%d %d has taken a fork\n", msecs_now(), philo->num);
	printf("%d %d is eating\n", msecs_now(), philo->num);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->mutex_arr[philo->num]);
	pthread_mutex_unlock(&philo->mutex_arr[philo->num - 1]);
	printf("%d %d is sleeping\n", msecs_now(), philo->num);
	usleep(philo->time_to_sleep);
	return (NULL);
}
*/
