/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:43:03 by smoon             #+#    #+#             */
/*   Updated: 2025/05/28 12:01:39 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_args	*init_arg_array(int argc, char *argv[])
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->run_flag = 1;
	mutex_init_and_atoi(args, argv);
	set_time_to_think(args);
	if (argc == 6)
		args->eat_target = ft_atoi(argv[5]);
	else
		args->eat_target = 0;
	args->start_time = 0;
	if (args->philo_num < 1 || args->time_to_die < 1
		|| args->time_to_eat < 1 || args->time_to_sleep < 1
		|| (argc == 6 && args->eat_target < 1))
	{
		ft_putstr_fd("Enter values 1 or above", 2);
		return (NULL);
	}
	else
		return (args);
}

pthread_mutex_t	*init_mutex(int num)
{
	int				i;
	pthread_mutex_t	*mutex_arr;

	i = 0;
	mutex_arr = malloc(num * sizeof(pthread_mutex_t));
	if (!mutex_arr)
		return (malloc_error(), NULL);
	while (i < num)
	{
		if (pthread_mutex_init(&mutex_arr[i], NULL) == -1)
		{
			uninit_mutex(mutex_arr, i);
			return (pthread_error("initialising mutexes"), NULL);
		}
		i++;
	}
	return (mutex_arr);
}

int	allocations(t_data *data, int argc, char *argv[])
{
	data->args = init_arg_array(argc, argv);
	if (!data->args)
		return (1);
	data->mutex_arr = init_mutex(data->args->philo_num);
	if (!data->mutex_arr)
		return (1);
	if (init_forks(&data->forks, data->args->philo_num, data->mutex_arr) != 0)
		return (1);
	data->thread_arr = malloc(data->args->philo_num * sizeof(pthread_t));
	if (allocate_philos(data) != 0)
		return (1);
	return (0);
}

int	init_even_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->philo_num)
	{
		if (i == data->args->philo_num - 1)
			usleep(10);
		if (pthread_create(&data->thread_arr[i], NULL,
				&start_sim, data->philo_arr[i]) != 0)
			return (1);
		i += 2;
	}
	return (0);
}

int	init_odd_threads(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->args->philo_num)
	{
		if (pthread_create(&data->thread_arr[i], NULL,
				&start_sim, data->philo_arr[i]) != 0)
			return (1);
		i += 2;
	}
	return (0);
}
