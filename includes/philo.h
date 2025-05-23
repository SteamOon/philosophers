/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:36:01 by smoon             #+#    #+#             */
/*   Updated: 2025/05/23 14:36:33 by smoon            ###   ########.fr       */
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

typedef struct s_args
{
	char			run_flag;
	pthread_mutex_t	run_mutex;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				eat_target;
	long			start_time;
}	t_args;

typedef struct s_philo
{
	int				num;
	int				*left_fork;
	int				*right_fork;
	int				eat_count;
	int				last_meal;
	pthread_mutex_t	eat_time_mutex;
	pthread_mutex_t	eat_count_mutex;
	t_args			*args;
	pthread_mutex_t	*left_mutex;
	pthread_mutex_t	*right_mutex;
}	t_philo;

typedef struct s_data
{
	pthread_t		monitor;
	t_args			*args;
	t_philo			**philo_arr;
	pthread_t		*thread_arr;
	pthread_mutex_t	*mutex_arr;
	int				*forks;
}	t_data;

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
int				allocate_philos(t_data *data);
int				initialise_forks(int **fork_arr, int num, pthread_mutex_t *mutex_arr);
pthread_mutex_t	*initialise_mutex(int num);
int				initialise_even_threads(pthread_t **thread_arr, t_philo **philo_arr, int num);
int				initialise_odd_threads(pthread_t **thread_arr, t_philo **philo_arr, int num);

//monitoring
void			*monitor_threads(void *data_ptr);

//testing
void			print_args(t_args args);
void			print_philos(t_philo **philo_arr);
void			print_forks(t_data *data);

//uninitialisers
int				free_philos(t_philo **philo_arr, int num);
int				uninitialise_mutex(pthread_mutex_t *mutex_arr, int num);
int				join_even_threads(pthread_t **thread_arr, int num);
int				join_odd_threads(pthread_t **thread_arr, int num);

//utils
long			msecs_now(void);
char			is_running(t_args *args);
int				cur_time(long start_time);
long			start_time(void);

#endif
