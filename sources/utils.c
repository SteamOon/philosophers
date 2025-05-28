/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:39:49 by smoon             #+#    #+#             */
/*   Updated: 2025/05/28 11:46:30 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char	is_running(t_args *args)
{
	char	result;

	pthread_mutex_lock(&args->run_mutex);
	result = args->run_flag;
	pthread_mutex_unlock(&args->run_mutex);
	return (result);
}

// printf("Philo %d create time: %ld\n", philo_arr[i]->num,
	// get_millisecs(philo_arr[i]->time_last_ate, args.start_time));
int	cur_time(long start_time)
{
	struct timeval	time;
	long			time_now;

	gettimeofday(&time, NULL);
	time_now = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_now - start_time);
}

long	start_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	precise_wait(int wait)
{
	long	time_stop;
	long	current_time;

	time_stop = start_time();
	if (time_stop == 0)
		return (1);
	time_stop += wait;
	while (1)
	{
		current_time = start_time();
		if (current_time == 0)
			return (1);
		if (current_time >= time_stop)
			break ;
		usleep((wait * 1000) / 100000);
	}
	return (0);
}
