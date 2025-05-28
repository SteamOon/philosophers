/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:52:04 by smoon             #+#    #+#             */
/*   Updated: 2025/05/28 12:38:40 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	wait_for_start(t_philo *philo)
{
	if (philo->args->philo_num % 2 != 0 && philo->num == philo->args->philo_num)
	{
		think_print(philo);
		precise_wait(philo->args->time_to_think);
	}
}

static void	*unlock_and_return(t_philo *philo, char left_flag, char right_flag)
{
	if (left_flag == 1)
		pthread_mutex_unlock(philo->left_mutex);
	if (right_flag == 1)
		pthread_mutex_unlock(philo->right_mutex);
	return (NULL);
}

static void	second_fork_and_eat(t_philo *philo)
{
	fork_print(philo);
	eat_print(philo);
	update_eat_stats(philo);
	precise_wait(philo->args->time_to_eat);
}

void	*odd_eating(t_philo *philo)
{
	wait_for_start(philo);
	while (still_eating(philo))
	{
		pthread_mutex_lock(philo->left_mutex);
		if (is_running(philo->args) == 0)
			return (unlock_and_return(philo, 1, 0));
		*philo->left_fork = philo->num;
		fork_print(philo);
		pthread_mutex_lock(philo->right_mutex);
		if (is_running(philo->args) == 0)
			return (unlock_and_return(philo, 1, 1));
		*philo->right_fork = philo->num;
		second_fork_and_eat(philo);
		pthread_mutex_unlock(philo->right_mutex);
		pthread_mutex_unlock(philo->left_mutex);
		if (is_running(philo->args) == 0)
			break ;
		sleep_print(philo);
		precise_wait(philo->args->time_to_sleep);
		if (is_running(philo->args) == 0)
			break ;
		think_print(philo);
		wait_before_eat(philo);
	}
	return (NULL);
}

void	*even_eating(t_philo *philo)
{
	wait_for_start(philo);
	while (still_eating(philo))
	{
		if (is_running(philo->args) == 0)
			break ;
		think_print(philo);
		wait_before_eat(philo);
		pthread_mutex_lock(philo->right_mutex);
		if (is_running(philo->args) == 0)
			return (unlock_and_return(philo, 0, 1));
		*philo->right_fork = philo->num;
		fork_print(philo);
		pthread_mutex_lock(philo->left_mutex);
		if (is_running(philo->args) == 0)
			return (unlock_and_return(philo, 1, 1));
		*philo->left_fork = philo->num;
		second_fork_and_eat(philo);
		pthread_mutex_unlock(philo->left_mutex);
		pthread_mutex_unlock(philo->right_mutex);
		if (is_running(philo->args) == 0)
			break ;
		sleep_print(philo);
		precise_wait(philo->args->time_to_sleep);
	}
	return (NULL);
}
