/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:21:56 by smoon             #+#    #+#             */
/*   Updated: 2025/05/23 15:08:16 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int get_last_eat_time(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->eat_time_mutex);
	time = philo->last_meal;
	pthread_mutex_unlock(&philo->eat_time_mutex);
	return (time);
}

static int	has_eaten_enough(t_philo *philo)
{
	int	eat_count;

	pthread_mutex_lock(&philo->eat_count_mutex);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	if (eat_count >= philo->args->eat_target)
		return (1);
	else
		return (0);
}

void	*monitor_threads(void *data_ptr)
{
	int			i;
	t_data	*data;

	data = (t_data *)data_ptr;
	while (1)
	{
		i = 0;
		while (data->philo_arr[i])
		{
			if (data->args->time_to_die + get_last_eat_time(data->philo_arr[i])
				<= cur_time(data->args->start_time))
			{
				pthread_mutex_lock(&data->args->run_mutex);
				printf("%d %d died\n", cur_time(data->args->start_time), data->philo_arr[i]->num);
				data->args->run_flag = 0;
				pthread_mutex_unlock(&data->args->run_mutex);
				break ;
			}
			if (data->args->eat_target != 0 && i == 0)
			{
				while (data->philo_arr[i])
				{
					if (has_eaten_enough(data->philo_arr[i]) != 1)
						break ;
					i++;
				}
				if (!data->philo_arr[i])
				{
					pthread_mutex_lock(&data->args->run_mutex);
					data->args->run_flag = 0;
					pthread_mutex_unlock(&data->args->run_mutex);
					break ;
				}
				i = 0;
			}
			i++;
		}
		if (is_running(data->args) == 0)
			break ;
	}
	return (NULL);
}
