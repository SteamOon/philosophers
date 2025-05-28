/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoon <smoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:36:01 by smoon             #+#    #+#             */
/*   Updated: 2025/05/28 11:59:51 by smoon            ###   ########.fr       */
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
	pthread_mutex_t	printf_mutex;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				eat_target;
	long			start_time;
	pthread_mutex_t	start_t_mutex;
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
void			*even_eating(t_philo *philo);
void			*odd_eating(t_philo *philo);
//eating2
void			*single_eating(t_philo *philo);
int				still_eating(t_philo *philo);
void			update_eat_stats(t_philo *philo);
void			wait_before_eat(t_philo *philo);

//errors
int				arg_num_error(int argc);
int				malloc_error(void);
int				numeric_check(char **argv);
int				pthread_error(char *desc);

//ft
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			ft_putstr_fd(char *s, int fd);

//init
int				allocate_philos(t_data *data);
int				init_forks(int **fork_arr, int num, pthread_mutex_t *mutex_arr);
//init2
int				allocations(t_data *data, int argc, char *argv[]);
t_args			*init_arg_array(int argc, char *argv[]);
pthread_mutex_t	*init_mutex(int num);
int				init_even_threads(t_data *data);
int				init_odd_threads(t_data *data);

//main
void			mutex_init_and_atoi(t_args *args, char *argv[]);
void			set_time_to_think(t_args *args);

//monitoring
void			*monitor_threads(t_data *data);

//printing
int				eat_print(t_philo *philo);
int				died_print(int time, int num, pthread_mutex_t *mutex);
int				fork_print(t_philo *philo);
int				sleep_print(t_philo *philo);
int				think_print(t_philo *philo);

//simulation
void			*start_sim(void *philo_ptr);
void			*start_monitor(void *philo_ptr);

//testing
void			print_args(t_args *args);
void			print_philos(t_philo **philo_arr);
void			print_forks(t_data *data);

//uninit
int				free_philos(t_philo **philo_arr, int num);
int				uninit_mutex(pthread_mutex_t *mutex_arr, int num);
void			wait_for_threads_and_end(t_data *data);

//utils
char			is_running(t_args *args);
int				cur_time(long start_time);
long			start_time(void);
int				precise_wait(int wait);

#endif
