/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:06:59 by ixu               #+#    #+#             */
/*   Updated: 2024/04/11 12:07:50 by ixu              ###   ########.fr       */
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

# include <semaphore.h>

typedef struct s_data	t_data;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef enum e_state
{
	TOOK_LEFT_FORK,
	TOOK_RIGHT_FORK,
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

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		last_meal_time;
	t_data		*data;
}	t_philo;

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
};

#endif