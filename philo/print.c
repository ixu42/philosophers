/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:59:28 by ixu               #+#    #+#             */
/*   Updated: 2024/04/10 17:12:29 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_state_debug(t_state state, t_philo *philo, long time)
{
	int	l_fork;
	int	r_fork;
	int	philo_idx;
	int	philo_count;

	philo_idx = philo->id - 1;
	philo_count = philo->data->philo_count;
	l_fork = philo_idx;
	r_fork = (philo_idx - 1 + philo_count) % philo_count;
	if (!philo->data->end_simulation)
	{
		if (state == TOOK_LEFT_FORK)
			printf("%-5ld %d has taken fork[%d]\n", time, philo->id, l_fork);
		else if (state == TOOK_RIGHT_FORK)
			printf("%-5ld %d has taken fork[%d]\n", time, philo->id, r_fork);
		else if (state == EATING)
			printf("%s%-5ld %d is eating%s\n", GREEN, time, philo->id, END);
		else if (state == SLEEPING)
			printf("%-5ld %d is sleeping\n", time, philo->id);
		else if (state == THINKING)
			printf("%-5ld %d is thinking\n", time, philo->id);
		else if (state == DIED)
			printf("%s%-5ld %d died%s\n", RED, time, philo->id, END);
	}
}

int	print_state(t_state state, t_philo *philo, t_bool debug_mode)
{
	long	time;

	if (safe_mutex(MUTEX_LOCK, &philo->data->mutex, philo->data))
		return (1);
	time = get_time(MILLISEC, philo->data) - philo->data->sim_start_time;
	if (time == -1)
		return (1);
	if (debug_mode)
		print_state_debug(state, philo, time);
	else if (!debug_mode && !philo->data->end_simulation)
	{
		if (state == TOOK_LEFT_FORK || state == TOOK_RIGHT_FORK)
			printf("%ld %d has taken a fork\n", time, philo->id);
		else if (state == EATING)
			printf("%ld %d is eating\n", time, philo->id);
		else if (state == SLEEPING)
			printf("%ld %d is sleeping\n", time, philo->id);
		else if (state == THINKING)
			printf("%ld %d is thinking\n", time, philo->id);
		else if (state == DIED)
			printf("%ld %d died\n", time, philo->id);
	}
	if (safe_mutex(MUTEX_UNLOCK, &philo->data->mutex, philo->data))
		return (1);
	return (0);
}
