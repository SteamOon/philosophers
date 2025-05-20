/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:36:08 by smoon             #+#    #+#             */
/*   Updated: 2025/05/20 16:49:25 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	initialise_arg_array(t_args *args, int argc, char *argv[])
{
	args->philo_num = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->eat_count = ft_atoi(argv[5]);
	else
		args->eat_count = 0;
}

/* void	*eating_test(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->mutex_arr[*philo->left_fork]);
	printf("%ld %d has taken a fork\n", msecs_now(), philo->num);
	pthread_mutex_lock(&philo->mutex_arr[*philo->right_fork]);
	printf("%ld %d has taken a fork\n", msecs_now(), philo->num);
	printf("%ld %d is eating\n", msecs_now(), philo->num);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->mutex_arr[*philo->left_fork]);
	pthread_mutex_unlock(&philo->mutex_arr[*philo->right_fork]);
	printf("%ld %d is sleeping\n", msecs_now(), philo->num);
	usleep(philo->time_to_sleep);
	printf("%ld %d is thinking\n", msecs_now(), philo->num);
	return (NULL);
} */

int	main(int argc, char *argv[])
{
	t_args	args;

	gettimeofday(&args.start_time, NULL);
	if (argc < 5 || argc > 6)
		return (arg_num_error(argc));
	if (numeric_check(argv) != 0)
		return (1);
	initialise_arg_array(&args, argc, argv);
	args.mutex_arr = initialise_mutex(args.philo_num);
	if (!args.mutex_arr)
		return (1);
	if (initialise_forks(&args.forks, args.philo_num, args.mutex_arr) != 0)
		return (1);
	if (allocate_philos(&args) != 0)
		return (1);
	args.thread_arr = malloc(args.philo_num * sizeof(pthread_t));
	// eating_test(args.philo_arr[0]);
	print_args(args);
	print_philos(args.philo_arr);
	print_forks(&args);
	if (initialise_even_threads(&args.thread_arr, args.philo_arr, args.philo_num) != 0)
		return (1);
	if (initialise_odd_threads(&args.thread_arr, args.philo_arr, args.philo_num) != 0)
		return (1);
	join_even_threads(&args.thread_arr, args.philo_num);
	join_odd_threads(&args.thread_arr, args.philo_num);
	uninitialise_mutex(args.mutex_arr, args.philo_num);
	free_philos(args.philo_arr, args.philo_num);
	free(args.forks);
}

