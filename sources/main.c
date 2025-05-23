/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:36:08 by smoon             #+#    #+#             */
/*   Updated: 2025/05/23 15:18:02 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	initialise_arg_array(t_args *args, int argc, char *argv[])
{
	pthread_mutex_init(&args->run_mutex, NULL);
	args->run_flag = 1;
	args->philo_num = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->time_to_think = args->time_to_eat / 10;
	if (argc == 6)
		args->eat_target = ft_atoi(argv[5]);
	else
		args->eat_target = 0;
	if (args->philo_num < 1 || args->time_to_die < 1
		|| args->time_to_eat < 1 || args->time_to_sleep < 1
		|| (argc == 6 && args->eat_target < 1))
	{
		ft_putstr_fd("Enter values 1 or above", 2);
		return (1);
	}
	else
		return (0);
}

int	main(int argc, char *argv[])
{
	t_args	args;
	t_data	data;

	data.args = &args;
	args.start_time = cur_time(0);
	if (argc < 5 || argc > 6)
		return (arg_num_error(argc));
	if (numeric_check(argv) != 0)
		return (1);
	if (initialise_arg_array(&args, argc, argv) != 0)
		return (1);
	data.mutex_arr = initialise_mutex(args.philo_num);
	if (!data.mutex_arr)
		return (1);
	if (initialise_forks(&data.forks, args.philo_num, data.mutex_arr) != 0)
		return (1);
	data.thread_arr = malloc(args.philo_num * sizeof(pthread_t));
	if (allocate_philos(&data) != 0)
		return (1);
	print_args(args);
	print_philos(data.philo_arr);
	print_forks(&data);
	if (initialise_even_threads(&data.thread_arr, data.philo_arr, args.philo_num) != 0)
		return (1);
	if (initialise_odd_threads(&data.thread_arr, data.philo_arr, args.philo_num) != 0)
		return (1);
	pthread_create(&data.monitor, NULL, &monitor_threads, &data);
	join_odd_threads(&data.thread_arr, args.philo_num);
	join_even_threads(&data.thread_arr, args.philo_num);
	pthread_join(data.monitor, NULL);
	uninitialise_mutex(data.mutex_arr, args.philo_num);
	pthread_mutex_destroy(&args.run_mutex);
	free_philos(data.philo_arr, args.philo_num);
	free(data.thread_arr);
	free(data.forks);
}

