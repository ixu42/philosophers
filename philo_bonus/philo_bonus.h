/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:06:59 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 21:58:44 by ixu              ###   ########.fr       */
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
# include <sys/wait.h>

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

# define USAGE "Usage: ./philo_bonus <num_of_philos> <time_to_die> <time_to_eat> \
<time_to_sleep> [num_of_times_each_philo_must_eat]\n"
# define ERR_MALLOC "malloc() error\n"
# define ERR_FORK "fork() error\n"
# define ERR_WAITPID "waitpid() error\n"
# define ERR_PTHREAD_CREATE "pthread_create() error\n"
# define ERR_PTHREAD_JOIN "pthread_join() error\n"
# define ERR_SEM_OPEN "sem_open() error\n"
# define ERR_SEM_WAIT "sem_wait() error\n"
# define ERR_SEM_POST "sem_post() error\n"
# define ERR_SEM_CLOSE "sem_close() error\n"
# define ERR_GETTIMEOFDAY "gettimeofday() error\n"
# define ERR_USLEEP "usleep() error\n"

// for debugging purpose
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
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_state;

typedef enum e_sim_state
{
	ACTIVE,
	PHILO_FULL,
	PHILO_DIED,
	OTHER_PHILO_DIED
}	t_sim_state;

typedef enum e_time_unit
{
	MICROSEC,
	MILLISEC
}	t_time_unit;

typedef enum e_func
{
	SEM_WAIT,
	SEM_POST,
	SEM_CLOSE,
}	t_func;

struct s_data
{
	int			id;
	sem_t		*sem;
	char		*sem_name;
	int			meals_eaten;
	long		last_meal_time;
	t_sim_state	sim_state;
	long		philo_count;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meals_limit;
	long		sim_start_time;
	sem_t		*forks;
	sem_t		*write;
};

// utils_bonus.c
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
int			ft_putstr_fd(char *s, int fd);
char		*ft_strjoin(char const *s1, char const *s2);

// ft_atol_bonus.c
long		ft_atol(char *str);

// ft_itoa_bonus.c
char		*ft_itoa(int n);

// time_bonus.c
long		get_time(t_time_unit time_unit);
void		ft_usleep(long microsec);

// semaphore_bonus.c
void		init_semaphores(t_data *data);
void		close_all_sems(t_data *data);
void		unlink_all_sems(void);
void		sem_handler(t_func func, sem_t *sem);

// simulate_bonus.c
int			simulate(t_data *data);

// routine_bonus.c
void		clean_exit(char *err_msg, t_data *data);
void		init_philo(t_data *data, int i);
void		arrange_eating(t_data *data, long time_to_eat);
t_bool		sim_should_end(t_data *data);
void		routine(t_data *data, int i);

// monitoring_bonus.c
t_bool		other_philo_died(t_data *data);
void		*monitoring(void *arg);

// eat_bonus.c
int			eat(t_data *data);
void		eat_alone(t_data *data);

// print_bonus.c
void		print_state(t_state state, t_data *data);

// getters_bonus.c
t_sim_state	get_sim_state(t_data *data);
long		get_meals_eaten(t_data *data);
long		get_last_meal_time(t_data *data);
long		get_time_to_die(t_data *data);

// setters_bonus.c
void		set_last_meal_time(t_data *data);
void		increment_meal_counter(t_data *data);
void		set_sim_state(t_data *data, t_sim_state sim_state);

#endif