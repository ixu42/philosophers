/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:18:31 by ixu               #+#    #+#             */
/*   Updated: 2024/04/16 16:50:37 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	drop_forks(t_data *data)
{
	safe_sem(SEM_POST, data->forks, data);
	safe_sem(SEM_POST, data->forks, data);
}

static int	take_forks(t_data *data)
{
	safe_sem(SEM_WAIT, data->forks, data);
	print_state(TOOK_1ST_FORK, data);
	if (sim_should_end(data))
	{
		safe_sem(SEM_POST, data->forks, data);
		return (1);
	}
	safe_sem(SEM_WAIT, data->forks, data); // drop first fork
	print_state(TOOK_2ND_FORK, data);
	if (sim_should_end(data))
	{
		drop_forks(data);
		return (1);
	}
	return (0);
}

static void	eating(t_data *data, long time_to_eat)
{
	set_last_meal_time(data);
	print_state(EATING, data);
	ft_usleep(time_to_eat, data);
	increment_meal_counter(data);
}

int	eat(t_data *data, long time_to_eat)
{
	if (take_forks(data))
		return (1);
	eating(data, time_to_eat);
	drop_forks(data);
	return (0);
}

/*
	simulate a philo with a fork. In such case, the philo 
	cannot eat and will die eventually after lapse of 
	time_to_die ms since the start of simulation.
*/

void	eat_alone(t_data *data)
{
	print_state(TOOK_1ST_FORK, data);
	ft_usleep(get_time_to_die(data) + 2000, data);
}
