/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:36:01 by smoon             #+#    #+#             */
/*   Updated: 2025/05/20 17:03:10 by smoon            ###   ########.fr       */
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
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	eat_count;
	struct timeval	time_last_ate;
	pthread_mutex_t	*mutex_arr;
	pthread_mutex_t	*left_mutex;
	pthread_mutex_t	*right_mutex;
}	t_philo;

typedef struct s_args
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_count;
	struct timeval	start_time;
	t_philo			**philo_arr;
	pthread_t		*thread_arr;
	pthread_mutex_t	*mutex_arr;
	int				*forks;
}	t_args;

//eating
void			*even_eating(void *philo);
void			*odd_eating(void *ptr);

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
int				allocate_philos(t_args *args);
int				initialise_forks(int **fork_arr, int num, pthread_mutex_t *mutex_arr);
pthread_mutex_t	*initialise_mutex(int num);
int				initialise_even_threads(pthread_t **thread_arr, t_philo **philo_arr, int num);
int				initialise_odd_threads(pthread_t **thread_arr, t_philo **philo_arr, int num);

//testing
void			print_args(t_args args);
void			print_philos(t_philo **philo_arr);
void			print_forks(t_args *args);

//uninitialisers
int				free_philos(t_philo **philo_arr, int num);
int				uninitialise_mutex(pthread_mutex_t *mutex_arr, int num);
int				join_even_threads(pthread_t **thread_arr, int num);
int				join_odd_threads(pthread_t **thread_arr, int num);

//utils
long			msecs_now(void);

#endif
