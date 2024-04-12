/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:59:28 by ixu               #+#    #+#             */
/*   Updated: 2024/04/12 16:34:18 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_state_debug(t_state state, t_philo *philo, long time)
{
	int	fork1;
	int	fork2;
	int	philo_idx;
	int	philo_count;

	philo_idx = philo->id - 1;
	philo_count = philo->data->philo_count;
	fork1 = philo_idx;
	fork2 = (philo_idx - 1 + philo_count) % philo_count;
	if (!sim_ended(philo))
	{
		if (state == TOOK_1ST_FORK)
			printf("%-5ld %d has taken fork[%d]\n", time, philo->id, fork1);
		else if (state == TOOK_2ND_FORK)
			printf("%-5ld %d has taken fork[%d]\n", time, philo->id, fork2);
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

	if (safe_mutex(MUTEX_LOCK, &philo->data->write, philo->data))
		return (1);
	time = get_time(MILLISEC, philo->data) - philo->data->sim_start_time;
	if (time == -1)
		return (1);
	if (debug_mode)
		print_state_debug(state, philo, time);
	else if (!debug_mode && !sim_ended(philo))
	{
		if (state == TOOK_1ST_FORK || state == TOOK_2ND_FORK)
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
	if (safe_mutex(MUTEX_UNLOCK, &philo->data->write, philo->data))
		return (1);
	return (0);
}
