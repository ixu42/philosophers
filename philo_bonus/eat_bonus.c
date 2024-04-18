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
	// printf("%d has dropped both forks\n", data->id);
}

static int	take_forks(t_data *data)
{
	// printf("%d before taking first fork\n", data->id);
	safe_sem(SEM_WAIT, data->forks, data);
	// printf("%d has taken first fork\n", data->id);
	print_state(TOOK_1ST_FORK, data);
	if (sim_should_end(data))
	{
		// printf("%d sim should end!\n", data->id);
		safe_sem(SEM_POST, data->forks, data);
		return (1);
		// printf("%d has dropped first fork\n", data->id);
		// close_all_sems(data);
		// exit(EXIT_SUCCESS);
	}
	safe_sem(SEM_WAIT, data->forks, data); // drop first fork
	print_state(TOOK_2ND_FORK, data);
	// printf("%d has taken second fork\n", data->id);
	if (sim_should_end(data))
	{
		drop_forks(data);
		return (1);
		// close_all_sems(data);
		// exit(EXIT_SUCCESS);
	}
	return (0);
}

static void	eating(t_data *data, long time_to_eat)
{
	set_last_meal_time(data);
	// printf("%d last meal time:%ld\n", data->id, data->last_meal_time / 1000 - data->sim_start_time);
	print_state(EATING, data);
	// printf("%d after printing eating state\n", data->id);
	ft_usleep(time_to_eat, data);
	// printf("%d after sleep for eating\n", data->id);
	increment_meal_counter(data);
	// printf("%d after incrementing meals counter\n", data->id);
}

int	eat(t_data *data, long time_to_eat)
{
	if (take_forks(data))
		return (1);
	eating(data, time_to_eat);
	// printf("%d has just eaten\n", data->id);
	drop_forks(data);
	// printf("%d has drop forks\n", data->id);
	return (0);
}

/*
	simulate a philo with a fork. In such case, the philo 
	cannot eat and will die eventually after lapse of 
	time_to_die ms since the start of simulation.
*/

void	eat_alone(t_data *data)
{
	// printf("before print\n");
	print_state(TOOK_1ST_FORK, data);
	// printf("after print\n");
	ft_usleep(get_time_to_die(data), data);
	// printf("after lapse of time to die\n");
}
