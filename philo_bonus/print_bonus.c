/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:34:35 by ixu               #+#    #+#             */
/*   Updated: 2024/04/16 09:41:22 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_state(t_state state, t_data *data)
{
	long	time;
	t_sim_state	sim_state;

	safe_sem(SEM_WAIT, data->write, data);
	time = get_time(MILLISEC, data) - data->sim_start_time;
	sim_state = get_sim_state(data);
	if (sim_state == ACTIVE)
	{
		if (state == TOOK_1ST_FORK || state == TOOK_2ND_FORK)
			printf("%ld %d has taken a fork\n", time, data->id);
		else if (state == EATING)
			printf("%ld %d is eating\n", time, data->id);
		else if (state == SLEEPING)
			printf("%ld %d is sleeping\n", time, data->id);
		else if (state == THINKING)
			printf("%ld %d is thinking\n", time, data->id);
	}
	if (state == DIED && sim_state == PHILO_DIED)
		printf("%ld %d died\n", time, data->id);
	safe_sem(SEM_POST, data->write, data);
}
