/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:34:35 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 21:06:43 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_death_msg(t_data *data, long timestamp)
{
	if (DEBUG_MODE)
		printf("%s%ld %d died%s\n", RED, timestamp, data->id, END);
	else
		printf("%ld %d died\n", timestamp, data->id);
}

static void	print_state_msg(t_state state, t_data *data, long timestamp)
{
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
}

void	print_state(t_state state, t_data *data)
{
	long	timestamp;

	timestamp = get_time(MILLISEC) - data->sim_start_time;
	if (state == DIED)
	{
		print_death_msg(data, timestamp);
		return ;
	}
	sem_handler(SEM_WAIT, data->write);
	if (other_philo_died(data))
	{
		sem_handler(SEM_POST, data->write);
		return ;
	}
	print_state_msg(state, data, timestamp);
	sem_handler(SEM_POST, data->write);
}
