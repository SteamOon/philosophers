/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:50:26 by smoon             #+#    #+#             */
/*   Updated: 2025/05/20 17:30:13 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_args(t_args args)
{
	printf("Number of philos: %4d\n", args.philo_num);
	printf("     Time to die: %4d\n", args.time_to_die);
	printf("   Time to sleep: %4d\n", args.time_to_sleep);
	printf("     Time to eat: %4d\n", args.time_to_eat);
	printf("    Times to eat: %4d\n", args.eat_count);

}

void	print_philos(t_philo **philo_arr)
{
	int	i;

	i = 0;
	while (philo_arr[i])
	{
		printf("Philo %3d: Left fork: %p (%d), M:%p\n", philo_arr[i]->num, philo_arr[i]->left_fork, *philo_arr[i]->left_fork, philo_arr[i]->left_mutex);
		printf("      %3d Right fork: %p (%d), M:%p\n", i, philo_arr[i]->right_fork, *philo_arr[i]->right_fork, philo_arr[i]->right_mutex);
		i++;
	}
}

void	print_forks(t_args *args)
{
	int	i;

	i = 0;
	printf("forks: ");
	while (i < args->philo_num)
	{
		printf("%d, ", args->forks[i]);
		i++;
	}
	printf("\n");
}
