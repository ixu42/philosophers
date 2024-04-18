/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:34:35 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 12:38:47 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_state(t_state state, t_data *data)
{
	long	timestamp;

	timestamp = get_time(MILLISEC, data) - data->sim_start_time;
	// printf("%d time:%ld\n", data->id, time);
	// sim_state = get_sim_state(data);
	// printf("%d sim_state in print state:%d\n", data->id, sim_state);
	if (state == DIED)
	{
		if (DEBUG_MODE)
			printf("%s%ld %d died%s\n", RED, timestamp, data->id, END);
		else
			printf("%ld %d died\n", timestamp, data->id);
		return ;
	}
	safe_sem(SEM_WAIT, data->write, data);
	if (someone_died(data))
	{
		safe_sem(SEM_POST, data->write, data);
		return ;
	}	
	if (state == TOOK_1ST_FORK || state == TOOK_2ND_FORK)
		printf("%ld %d has taken a fork\n", timestamp, data->id);
	else if (!DEBUG_MODE && state == EATING)
		printf("%ld %d is eating\n", timestamp, data->id);
	else if (DEBUG_MODE && state == EATING)
		printf("%s%ld %d is eating%s\n", GREEN, timestamp, data->id, END);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", timestamp, data->id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", timestamp, data->id);
	safe_sem(SEM_POST, data->write, data);
}
