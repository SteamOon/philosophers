/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:02:03 by smoon             #+#    #+#             */
/*   Updated: 2025/05/26 13:23:59 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ready_to_start(t_args *args)
{
	int	ret;

	pthread_mutex_lock(&args->start_t_mutex);
	ret = args->start_time;
	pthread_mutex_unlock(&args->start_t_mutex);
	return (ret);
}

void	*start_sim(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (ready_to_start(philo->args) == 0)
		usleep(1);
	if (philo->num % 2 == 0)
		even_eating(philo);
	else
		odd_eating(philo);
	return (NULL);
}

void	*start_monitor(void *data_ptr)
{
	t_data	*data;

	data = (t_data *)data_ptr;
	while (ready_to_start(data->args) == 0)
		usleep(1);
	monitor_threads(data);
	return (NULL);
}
