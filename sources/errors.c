/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:50 by smoon             #+#    #+#             */
/*   Updated: 2025/05/28 10:14:05 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	arg_num_error(int argc)
{
	if (argc > 6)
		ft_putstr_fd("Too many arguments!\n", 2);
	else
		ft_putstr_fd("Not enough arguments!\n", 2);
	return (1);
}

int	malloc_error(void)
{
	ft_putstr_fd("Error allocating memory\n", 2);
	return (1);
}

static int	non_numeric_error(void)
{
	ft_putstr_fd("Please enter positive numeric arguments.\n", 2);
	return (1);
}

int	numeric_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] && ft_isdigit(argv[i][j]))
			j++;
		if (argv[i][j] != 0)
			return (non_numeric_error());
		i++;
	}
	return (0);
}

int	pthread_error(char *desc)
{
	ft_putstr_fd("Encountered pthread error when ", 2);
	ft_putstr_fd(desc, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
