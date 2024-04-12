/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:10:56 by ixu               #+#    #+#             */
/*   Updated: 2024/04/12 16:48:18 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// write, usleep
# include <unistd.h>

// printf
# include <stdio.h>

// malloc, free
# include <stdlib.h>

// INT_MAX, INT_MIN
# include <limits.h>

/*
	pthread_create, pthread_join, pthread_mutex_init, pthread_mutex_lock, 
	pthread_mutex_unlock, pthread_mutex_destroy 
*/
# include <pthread.h>

// gettimeofday
# include <sys/time.h>

// macros for error handling
# define USAGE "Usage: ./philo [num_of_philos] [time_to_die] [time_to_eat] \
[time_to_sleep] [num_of_times_each_philo_must_eat](optional)\n"
# define ERR_CREATE "pthread_create error\n"
# define ERR_JOIN "pthread_join error\n"
# define ERR_MUTEX_LOCK "pthread_mutex_lock error\n"
# define ERR_MUTEX_UNLOCK "pthread_mutex_unlock error\n"
# define ERR_MUTEX_DESTROY "pthread_mutex_destroy error\n"

// macros for debugging purpose
# define DEBUG_MODE 0
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define END "\033[0m"

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mutex;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef enum e_state
{
	TOOK_1ST_FORK,
	TOOK_2ND_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_state;

typedef enum e_time_unit
{
	MICROSEC,
	MILLISEC
}	t_time_unit;

/* 
	for handling function errors, ex. typically pthread or mutex related
	functions a non-zero return value indicates error.
*/

typedef enum e_func
{
	CREATE,
	JOIN,
	MUTEX_LOCK,
	MUTEX_UNLOCK,
	MUTEX_DESTROY,
	GETTIMEOFDAY,
	USLEEP
}	t_func;

// mutex: for coordinating data accesses between the philo and the monitor

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			meals_eaten;
	long		last_meal_time;
	t_mutex		*first_fork;
	t_mutex		*second_fork;
	t_mutex		mutex;
	t_data		*data;
}	t_philo;

/*
	philo_count: argv[1], total number of philosophers
	time_to_die: argv[2], converted to microseconds
	time_to_eat: argv[3], converted to microseconds
	time_to_sleep: argv[4], converted to microseconds
	meals_limit: argv[5], optional argument
	sim_start_time: starting time of simulation in microseconds
	start_simulation: a flag to indicate if all philos/threads have been created
	end_simulation: a flag to denote end of simulation due to death of 
					any philo, or meals limits of all philos being reached
	monitor: a thread continuously checking if the simulation should end
	mutex: for coordinating data accesses by different threads (incl. philos 
			and monitor)
	write: for coordinating printing state messages by different threads
	*forks: a pointer to an array of forks(mutexes)
	*philos: a pointer to an array of philos(threads)
*/

struct s_data
{
	long		philo_count;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meals_limit;
	long		sim_start_time;
	t_bool		start_simulation;
	t_bool		end_simulation;
	pthread_t	monitor;
	t_mutex		mutex;
	t_mutex		write;
	t_mutex		*forks;
	t_philo		*philos;
};

// utils.c
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_putstr_fd(char *s, int fd);
long	get_time(t_time_unit time_unit, t_data *data);
int		ft_usleep(long microsec, t_data *data);

// ft_atol.c
long	ft_atol(char *str);

// init_data.c
int		init_data(t_data *data, char **argv);

// init_mutex.c
int		init_all_mutexes(t_data *data);

// simulate.c
int		simulate(t_data *data);

// eat.c
int		eat_alone(t_philo *philo);
int		eat(t_philo *philo);

// monitor.c
void	*monitoring(void *arg);

// print.c
int		print_state(t_state state, t_philo *philo, t_bool debug_mode);

/*
	the functions to prevent data races for read and write operations
	for data accessed by multiple threads concurrently.
*/
// getters_1.c
t_bool	sim_ended(t_philo *philo);
t_bool	sim_started(t_data *data);
long	get_meals_eaten(t_philo *philo);
long	get_last_meal_time(t_philo *philo);
// getters_2.c
long	get_philo_count(t_data *data);
long	get_time_to_eat(t_philo *philo);
long	get_time_to_sleep(t_philo *philo);
long	get_time_to_die(t_data *data);
// setters.c
int		set_last_meal_time(t_philo *philo);
int		increment_meal_counter(t_philo *philo);
void	set_end_sim(t_data *data);
int		end_sim(t_data *data);

// safe_funcs.c
int		destroy_all_mutexes(t_data *data);
int		safe_return(char *err_msg, t_data *data, t_func func);
int		safe_pthread(t_func func, pthread_t *thread,
			void *(*routine)(void *), void *arg);
int		safe_mutex(t_func func, t_mutex *mutex, t_data *data);

#endif