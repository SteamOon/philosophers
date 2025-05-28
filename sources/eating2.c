/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:08:30 by smoon             #+#    #+#             */
/*   Updated: 2025/05/28 12:02:05 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	still_eating(t_philo *philo)
{
	if (philo->args->eat_target == 0
		|| philo->eat_count < philo->args->eat_target)
		return (1);
	return (0);
}

void	*single_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_time_mutex);
	philo->last_meal = 0;
	pthread_mutex_unlock(&philo->eat_time_mutex);
	pthread_mutex_lock(philo->left_mutex);
	*philo->left_fork = philo->num;
	fork_print(philo);
	pthread_mutex_unlock(philo->left_mutex);
	return (NULL);
}

void	update_eat_stats(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_time_mutex);
	philo->last_meal = cur_time(philo->args->start_time);
	pthread_mutex_unlock(&philo->eat_time_mutex);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	return ;
}

void	wait_before_eat(t_philo *philo)
{
	int	wait;
	int	last_minute;
	int	now;

	last_minute = philo->last_meal + philo->args->time_to_die
		- philo->args->time_to_eat;
	now = cur_time(philo->args->start_time);
	wait = last_minute - now;
	if (wait < 1)
		wait = 1;
	precise_wait(wait * 0.995);
}
