/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:36:08 by smoon             #+#    #+#             */
/*   Updated: 2025/05/28 11:47:45 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	mutex_init_and_atoi(t_args *args, char *argv[])
{
	pthread_mutex_init(&args->printf_mutex, NULL);
	pthread_mutex_init(&args->run_mutex, NULL);
	pthread_mutex_init(&args->start_t_mutex, NULL);
	args->philo_num = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
}

void	set_time_to_think(t_args *args)
{
	if (args->philo_num % 2 == 0)
	{
		args->time_to_think = (args->time_to_die
				- args->time_to_eat - args->time_to_sleep) / 2 - 10;
		if (args->time_to_think < 1)
			args->time_to_think = 1;
	}
	else
		args->time_to_think = args->time_to_eat;
}

static void	set_start_time(t_data *data)
{
	pthread_mutex_lock(&data->args->start_t_mutex);
	data->args->start_time = start_time();
	pthread_mutex_unlock(&data->args->start_t_mutex);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (arg_num_error(argc));
	if (numeric_check(argv) != 0)
		return (1);
	if (allocations(&data, argc, argv) == 1)
		return (1);
	if (init_even_threads(&data) != 0)
		return (1);
	if (init_odd_threads(&data) != 0)
		return (1);
	pthread_create(&data.monitor, NULL, &start_monitor, &data);
	usleep(1000);
	set_start_time(&data);
	wait_for_threads_and_end(&data);
}

	// print_args(data.args);
	// print_philos(data.philo_arr);
	// print_forks(&data);
