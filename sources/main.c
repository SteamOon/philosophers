/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:36:08 by smoon             #+#    #+#             */
/*   Updated: 2025/05/19 16:50:29 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_args(t_args args)
{
	printf("Number of philos: %4d\n", args.philo_num);
	printf("     Time to die: %4d\n", args.time_to_die);
	printf("   Time to sleep: %4d\n", args.time_to_sleep);
	printf("     Time to eat: %4d\n", args.time_to_eat);
	printf("    Times to eat: %4d\n", args.eat_count);

}

static void	print_philos(t_philo **philo_arr)
{
	int	i;

	i = 0;
	while (philo_arr[i])
	{
		printf("Philo %3d: Left fork: %p\n", philo_arr[i]->num, philo_arr[i]->left_fork);
		printf("i     %3d Right fork: %p\n", i, philo_arr[i]->right_fork);
		i++;
	}
}

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

int	main(int argc, char *argv[])
{
	t_args			args;
	t_philo			**philo_arr;
	// pthread_t	*thread_arr;
	pthread_mutex_t	*mutex_arr;
	int				*forks;

	if (argc < 5 || argc > 6)
		return (arg_num_error(argc));
	if (numeric_check(argv) != 0)
		return (1);
	initialise_arg_array(&args, argc, argv);
	mutex_arr = initialise_mutex(args.philo_num);
	if (!mutex_arr)
		return (1);
	if (initialise_forks(&forks, args.philo_num, mutex_arr) != 0)
		return (1);
	philo_arr = allocate_philos(forks, args.philo_num, mutex_arr);
	if (!philo_arr)
		return (1);
	// if (initialise_threads(philo_arr, args.philo_num))
	print_args(args);
	print_philos(philo_arr);
	uninitialise_mutex(mutex_arr, args.philo_num);
	free_philos(philo_arr, args.philo_num + 1);
	free(forks);
}
