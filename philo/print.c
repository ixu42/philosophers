/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:59:28 by ixu               #+#    #+#             */
/*   Updated: 2024/04/13 14:58:21 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_state(t_state state, t_philo *philo)
{
	long	time;

	if (safe_mutex(MUTEX_LOCK, &philo->data->write, philo->data))
		return (1);
	time = get_time(MILLISEC, philo->data) - philo->data->sim_start_time;
	if (time == -1)
		return (1);
	if (DEBUG_MODE)
		print_state_debug(state, philo, time);
	else if (!DEBUG_MODE && !sim_ended(philo))
	{
		if (state == TOOK_1ST_FORK || state == TOOK_2ND_FORK)
			printf("%ld %d has taken a fork\n", time, philo->id);
		else if (state == EATING)
			printf("%ld %d is eating\n", time, philo->id);
		else if (state == SLEEPING)
			printf("%ld %d is sleeping\n", time, philo->id);
		else if (state == THINKING)
			printf("%ld %d is thinking\n", time, philo->id);
	}
	if (!DEBUG_MODE && state == DIED)
		printf("%ld %d died\n", time, philo->id);
	if (safe_mutex(MUTEX_UNLOCK, &philo->data->write, philo->data))
		return (1);
	return (0);
}
