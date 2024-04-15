/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:18:31 by ixu               #+#    #+#             */
/*   Updated: 2024/04/14 23:37:44 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	drop_forks(t_philo *philo)
{
	// if (DEBUG_MODE)
	// 	return (drop_forks_debug(philo, fork_to_drop));
	safe_sem(SEM_POST, philo->data->forks, philo->data);
	safe_sem(SEM_POST, philo->data->forks, philo->data);
}

static void	take_forks(t_philo *philo)
{
	safe_sem(SEM_WAIT, philo->data->forks, philo->data);
	print_state(TOOK_1ST_FORK, philo);
	if (sim_ended(philo))
		exit(EXIT_SUCCESS);
	safe_sem(SEM_WAIT, philo->data->forks, philo->data);
	print_state(TOOK_2ND_FORK, philo);
	if (sim_ended(philo))
		exit(EXIT_SUCCESS);
}

static void	eating(t_philo *philo)
{
	set_last_meal_time(philo);
	print_state(EATING, philo);
	ft_usleep(get_time_to_eat(philo), philo->data);
	increment_meal_counter(philo);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	if (sim_ended(philo))
		exit(EXIT_SUCCESS);
	eating(philo);
	drop_forks(philo);
}

/*
	simulate a philo with a fork. In such case, the philo 
	cannot eat and will die eventually after lapse of 
	time_to_die ms since the start of simulation.
*/

void	eat_alone(t_philo *philo)
{
	// printf("before print\n");
	print_state(TOOK_1ST_FORK, philo);
	// printf("after print\n");
	ft_usleep(get_time_to_die(philo->data), philo->data);
	// printf("after lapse of time to die\n");
}
