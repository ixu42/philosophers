/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:06:59 by ixu               #+#    #+#             */
/*   Updated: 2024/04/15 16:38:09 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// printf
# include <stdio.h>

// malloc, free, exit, EXIT_SUCCESS, EXIT_FAILURE
# include <stdlib.h>

// fork
# include <sys/types.h>
# include <unistd.h>

// waitpid
#include <sys/wait.h>

// pthread_create, pthread_join
# include <pthread.h>

// for O_* constants passed to sem_open
# include <fcntl.h>

// for mode constants passed to sem_open
# include <sys/stat.h>

// sem_open, sem_close, sem_unlink, sem_wait, sem_post
# include <semaphore.h>

// gettimeofday
# include <sys/time.h>

// INT_MAX, INT_MIN
# include <limits.h>

// kill
#include <signal.h>

# define USAGE "Usage: ./philo [num_of_philos] [time_to_die] [time_to_eat] \
[time_to_sleep] [num_of_times_each_philo_must_eat](optional)\n"
# define ERR_MALLOC "malloc() error\n"
# define ERR_FORK "fork() error\n"
# define ERR_WAITPID "waitpid() error\n"
# define ERR_CREATE "pthread_create() error\n"
# define ERR_JOIN "pthread_join() error\n"
# define ERR_SEM_OPEN "sem_open() error\n"
# define ERR_SEM_WAIT "sem_wait() error\n"
# define ERR_SEM_POST "sem_post() error\n"
# define ERR_SEM_CLOSE "sem_close() error\n"
# define ERR_GETTIMEOFDAY "gettimeofday() error\n"
# define ERR_USLEEP "usleep() error\n"

/*
	macros for debugging purpose
	change DEBUG_MODE to 1 to print more informative state messages
*/
# define DEBUG_MODE 0
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define END "\033[0m"

typedef struct s_data	t_data;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef enum e_state
{
	TOOK_1ST_FORK,
	TOOK_2ND_FORK,
	DROPPED_1ST_FORK,
	DROPPED_2ND_FORK,
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

typedef enum e_func
{
	CREATE,
	JOIN,
	SEM_WAIT,
	SEM_POST,
	SEM_CLOSE,
	GETTIMEOFDAY,
	USLEEP
}	t_func;

/* typedef struct s_philo
{
	int			id;
	pid_t		pid;
	int			meals_eaten;
	long		last_meal_time;
	t_data		*data;
}	t_philo; */

struct s_data
{
	int			id;
	int			meals_eaten;
	long		last_meal_time;
	long		philo_count;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meals_limit;
	long		sim_start_time;
	t_bool		end_simulation;
	pthread_t	monitor;
	sem_t		*forks;
	sem_t		*write;
	sem_t		*sem;
	sem_t		*a_philo_died;
	// sem_t		*full;
	// t_philo		*philos;
};

// utils_bonus.c
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_putstr_fd(char *s, int fd);
long	get_time(t_time_unit time_unit, t_data *data);
void	ft_usleep(long microsec, t_data *data);

// ft_atol_bonus.c
long	ft_atol(char *str);

// ft_itoa_bonus.c
char	*ft_itoa(int n); // to be removed?

// ft_strjoin_bonus.c
char	*ft_strjoin(char const *s1, char const *s2); // to be removed?

// init_bonus.c
void	init_data(t_data *data, char **argv);

// tbd
void	unlink_all_sems(void);

// simulate_bonus.c
void	simulate(t_data *data);

// monitoring_bonus.c
void	*monitoring(void *arg);

// eat_bonus.c
void	eat(t_data *data);
void	eat_alone(t_data *data);

// print_bonus.c
void	print_state(t_state state, t_data *data);

/*
	the functions to prevent data races for read and write operations
	for data accessed by multiple threads concurrently.
*/
// getter.c
t_bool	sim_ended(t_data *data);
t_bool	sim_started(t_data *data);
long	get_meals_eaten(t_data *data);
long	get_last_meal_time(t_data *data);
long	get_philo_count(t_data *data);
long	get_time_to_eat(t_data *data);
long	get_time_to_sleep(t_data *data);
long	get_time_to_die(t_data *data);
// setters.c
void	set_last_meal_time(t_data *data);
void	increment_meal_counter(t_data *data);
void	set_end_sim(t_data *data);

// safe_funcs_bonus.c
void	safe_exit(char *err_msg, t_data *data, t_func func);
void	safe_pthread(t_func func, pthread_t *thread,
		void *(*routine)(void *), void *arg);
void	safe_sem(t_func func, sem_t *sem, t_data *data);

#endif