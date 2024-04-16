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
	// if (DEBUG_MODE)
	// 	return (drop_forks_debug(philo, fork_to_drop));
	safe_sem(SEM_POST, data->forks, data);
	safe_sem(SEM_POST, data->forks, data);
}

static void	take_forks(t_data *data)
{
	printf("%d before taking first fork\n", data->id);
	safe_sem(SEM_WAIT, data->forks, data);
	print_state(TOOK_1ST_FORK, data);
	printf("%d has taken first fork\n", data->id);
	if (sim_should_end(data))
		exit(EXIT_SUCCESS);
	safe_sem(SEM_WAIT, data->forks, data);
	print_state(TOOK_2ND_FORK, data);
	printf("%d has taken second fork\n", data->id);
	if (sim_should_end(data))
		exit(EXIT_SUCCESS);
}

static void	eating(t_data *data)
{
	set_last_meal_time(data);
	print_state(EATING, data);
	printf("%d after printing eating state\n", data->id);
	ft_usleep(get_time_to_eat(data), data);
	printf("%d after sleep for eating\n", data->id);
	increment_meal_counter(data);
	printf("%d after incrementing meals counter\n", data->id);
}

void	eat(t_data *data)
{
	take_forks(data);
	// if (sim_should_end(data))
	// 	exit(EXIT_SUCCESS);
	eating(data);
	printf("%d has just eaten\n", data->id);
	drop_forks(data);
	printf("%d has drop forks\n", data->id);
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
