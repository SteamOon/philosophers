/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:36:08 by smoon             #+#    #+#             */
/*   Updated: 2025/05/26 17:12:06 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_args	*initialise_arg_array(int argc, char *argv[])
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	pthread_mutex_init(&args->printf_mutex, NULL);
	pthread_mutex_init(&args->run_mutex, NULL);
	pthread_mutex_init(&args->start_t_mutex, NULL);
	args->run_flag = 1;
	args->philo_num = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	// args->time_to_think = (args->time_to_die - args->time_to_eat - args->time_to_sleep) / 3;
	// if (args->time_to_think < 1)
	// 	args->time_to_think = 1;
	args->time_to_think = args->time_to_eat / 10;
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

static void	set_start_time(t_data *data)
{
	pthread_mutex_lock(&data->args->start_t_mutex);
	data->args->start_time = cur_time(0);
	pthread_mutex_unlock(&data->args->start_t_mutex);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (arg_num_error(argc));
	if (numeric_check(argv) != 0)
		return (1);
	data.args = initialise_arg_array(argc, argv);
	if (!data.args)
		return (1);
	data.mutex_arr = initialise_mutex(data.args->philo_num);
	if (!data.mutex_arr)
		return (1);
	if (initialise_forks(&data.forks, data.args->philo_num, data.mutex_arr) != 0)
		return (1);
	data.thread_arr = malloc(data.args->philo_num * sizeof(pthread_t));
	if (allocate_philos(&data) != 0)
		return (1);
	print_args(data.args);
	print_philos(data.philo_arr);
	print_forks(&data);
	if (initialise_even_threads(&data) != 0)
		return (1);
	if (initialise_odd_threads(&data) != 0)
		return (1);
	pthread_create(&data.monitor, NULL, &start_monitor, &data);
	usleep(1000);
	set_start_time(&data);
	join_odd_threads(&data.thread_arr, data.args->philo_num);
	join_even_threads(&data.thread_arr, data.args->philo_num);
	pthread_join(data.monitor, NULL);
	uninitialise_mutex(data.mutex_arr, data.args->philo_num);
	pthread_mutex_destroy(&data.args->run_mutex);
	pthread_mutex_destroy(&data.args->printf_mutex);
	pthread_mutex_destroy(&data.args->start_t_mutex);
	free_philos(data.philo_arr, data.args->philo_num);
	free(data.thread_arr);
	free(data.forks);
}

