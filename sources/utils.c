/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:39:49 by smoon             #+#    #+#             */
/*   Updated: 2025/05/27 10:30:18 by smoon            ###   ########.fr       */
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

long	msecs_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

// printf("Philo %d create time: %ld\n", philo_arr[i]->num, get_millisecs(philo_arr[i]->time_last_ate, args.start_time));
int	cur_time(long start_time)
{
	struct timeval	time;
	long			time_now;

	gettimeofday(&time, NULL);
	time_now = time.tv_sec * 1000000 + time.tv_usec;
	return (time_now - start_time);
}

long	start_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}
