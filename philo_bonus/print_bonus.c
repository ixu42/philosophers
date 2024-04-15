/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:34:35 by ixu               #+#    #+#             */
/*   Updated: 2024/04/15 15:14:15 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_state(t_state state, t_data *data)
{
	long	time;

	// printf("debug0\n");
	safe_sem(SEM_WAIT, data->write, data);
	// printf("debug1\n");
	time = get_time(MILLISEC, data) - data->sim_start_time;
	// printf("debug2\n");
	// if (DEBUG_MODE)
		// print_state_debug(state, philo, time);
	if (!DEBUG_MODE && !sim_ended(data))
	{
		// printf("debug3\n");
		if (state == TOOK_1ST_FORK || state == TOOK_2ND_FORK)
			printf("%ld %d has taken a fork\n", time, data->id);
		else if (state == EATING)
			printf("%ld %d is eating\n", time, data->id);
		else if (state == SLEEPING)
			printf("%ld %d is sleeping\n", time, data->id);
		else if (state == THINKING)
			printf("%ld %d is thinking\n", time, data->id);
	}
	// printf("debug4\n");
	if (!DEBUG_MODE && state == DIED)
		printf("%ld %d died\n", time, data->id);
	safe_sem(SEM_POST, data->write, data);
}
