/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:52:04 by smoon             #+#    #+#             */
/*   Updated: 2025/05/27 16:41:34 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	update_eat_stats(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_time_mutex);
	philo->last_meal = cur_time(philo->args->start_time);
	pthread_mutex_unlock(&philo->eat_time_mutex);
	// pthread_mutex_lock(&philo->args->printf_mutex);
	// printf("%d updated last meal %d\n", philo->num, philo->last_meal);
	// pthread_mutex_unlock(&philo->args->printf_mutex);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	return ;
}

/* static int	get_sleep_time(t_philo *philo,  int old_time)
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

	(void)old_time;
	time = philo->last_meal + philo->args->time_to_eat - cur_time(philo->args->start_time);
	if (time < 0)
		time = 0;
	return (time);
} */

// static void	wait_before_eat_loop(t_philo *philo)
// {
// 	while (cur_time(philo->args->start_time) + philo->args->time_to_eat < philo->last_meal - 30
// 		+ philo->args->time_to_die)
// 		usleep(50);
// }

static void	wait_before_eat(t_philo *philo)
{
	int	wait;
	int	last_minute;
	int	now;

	last_minute = philo->last_meal + philo->args->time_to_die - philo->args->time_to_eat;
	now = cur_time(philo->args->start_time);
	wait = last_minute - now;
	if (wait < 1)
		wait = 1;
	precise_wait(wait * 0.995);
}

void	*odd_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_time_mutex);
	philo->last_meal = 0;
	pthread_mutex_unlock(&philo->eat_time_mutex);
	if (philo->args->philo_num % 2 != 0 && philo->num == philo->args->philo_num)
	{
		think_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		precise_wait(philo->args->time_to_think);
	}
	while (philo->args->eat_target == 0 || philo->eat_count	< philo->args->eat_target)
	{
		// try_fork_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		pthread_mutex_lock(philo->left_mutex);
		if (is_running(philo->args) == 0)
		{
			pthread_mutex_unlock(philo->left_mutex);
			break ;
		}
		*philo->left_fork = philo->num;
		fork_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		pthread_mutex_lock(philo->right_mutex);
		if (is_running(philo->args) == 0)
		{
			pthread_mutex_unlock(philo->right_mutex);
			pthread_mutex_unlock(philo->left_mutex);
			break ;
		}
		*philo->right_fork = philo->num;
		fork_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		eat_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		update_eat_stats(philo);
		precise_wait(philo->args->time_to_eat);
		pthread_mutex_unlock(philo->right_mutex);
		pthread_mutex_unlock(philo->left_mutex);
		if (is_running(philo->args) == 0)
			break ;
		sleep_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		precise_wait(philo->args->time_to_sleep);
		if (is_running(philo->args) == 0)
			break ;
		think_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		// precise_wait(philo->args->time_to_think);
		// wait_before_eat_loop(philo);
		wait_before_eat(philo);
	}
	return (NULL);
}

void	*even_eating(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->eat_time_mutex);
	philo->last_meal = 0;
	pthread_mutex_unlock(&philo->eat_time_mutex);
	while (philo->args->eat_target == 0 || philo->eat_count	< philo->args->eat_target)
	{
		if (is_running(philo->args) == 0)
			break ;
		think_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		// precise_wait(philo->args->time_to_think);
		// wait_before_eat_loop(philo);
		wait_before_eat(philo);
		// try_fork_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		pthread_mutex_lock(philo->right_mutex);
		*philo->right_fork = philo->num;
		if (is_running(philo->args) == 0)
		{
			pthread_mutex_unlock(philo->right_mutex);
			break ;
		}
		fork_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		pthread_mutex_lock(philo->left_mutex);
		*philo->left_fork = philo->num;
		if (is_running(philo->args) == 0)
		{
			pthread_mutex_unlock(philo->left_mutex);
			pthread_mutex_unlock(philo->right_mutex);
			break ;
		}
		fork_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		time = eat_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		update_eat_stats(philo);
		precise_wait(philo->args->time_to_eat);
		pthread_mutex_unlock(philo->left_mutex);
		pthread_mutex_unlock(philo->right_mutex);
		if (is_running(philo->args) == 0)
			break ;
		sleep_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
		precise_wait(philo->args->time_to_sleep);
	}
	return (NULL);
}

void	*single_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_time_mutex);
	philo->last_meal = 0;
	pthread_mutex_unlock(&philo->eat_time_mutex);
	pthread_mutex_lock(philo->left_mutex);
	*philo->left_fork = philo->num;
	fork_print(philo->args->start_time, philo->num, &philo->args->printf_mutex);
	pthread_mutex_unlock(philo->left_mutex);
	return (NULL);
}
