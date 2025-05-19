/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:36:01 by smoon             #+#    #+#             */
/*   Updated: 2025/05/19 16:04:04 by smoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int	num;
	int	*left_fork;
	int	*right_fork;
}	t_philo;

typedef struct s_args
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_count;
}	t_args;

//errors
int				arg_num_error(int argc);
int				malloc_error(void);
int				numeric_check(char **argv);
int				pthread_error(char *desc);

//ft
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			ft_putstr_fd(char *s, int fd);

//initialisers
t_philo			**allocate_philos(int *forks, int num, pthread_mutex_t *mutex_arr);
int				initialise_forks(int **fork_arr, int num, pthread_mutex_t *mutex_arr);
pthread_mutex_t	*initialise_mutex(int num);

//uninitialisers
int				free_philos(t_philo **philo_arr, int num);
int				uninitialise_mutex(pthread_mutex_t *mutex_arr, int num);

#endif
