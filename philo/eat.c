/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:07:39 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 17:26:11 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	drop_forks(t_philo *philo, t_fork fork_to_drop)
{
	if (DEBUG_MODE)
		return (drop_forks_debug(philo, fork_to_drop));
	if (fork_to_drop == DROP_FORK_1)
	{
		if (safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data))
			return (end_sim(philo, DROP_NONE));
	}
	else if (fork_to_drop == DROP_FORK_2)
	{
		if (safe_mutex(MUTEX_UNLOCK, philo->second_fork, philo->data))
			return (end_sim(philo, DROP_NONE));
	}
	else if (fork_to_drop == DROP_BOTH)
	{
		if (safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data))
			return (end_sim(philo, DROP_NONE));
		if (safe_mutex(MUTEX_UNLOCK, philo->second_fork, philo->data))
			return (end_sim(philo, DROP_NONE));
	}
	return (0);
}

static int	take_forks(t_philo *philo)
{
	if (safe_mutex(MUTEX_LOCK, philo->first_fork, philo->data))
		return (end_sim(philo, DROP_NONE));
	if (print_state(TOOK_1ST_FORK, philo))
		return (end_sim(philo, DROP_FORK_1));
	if (sim_ended(philo))
		return (drop_forks(philo, DROP_FORK_1));
	if (safe_mutex(MUTEX_LOCK, philo->second_fork, philo->data))
		return (end_sim(philo, DROP_FORK_1));
	if (print_state(TOOK_2ND_FORK, philo))
		return (end_sim(philo, DROP_BOTH));
	if (sim_ended(philo))
		return (drop_forks(philo, DROP_BOTH));
	return (0);
}

static int	eating(t_philo *philo)
{
	if (set_last_meal_time(philo))
		return (end_sim(philo, DROP_BOTH));
	if (print_state(EATING, philo))
		return (end_sim(philo, DROP_BOTH));
	if (ft_usleep(get_time_to_eat(philo), philo->data))
		return (end_sim(philo, DROP_BOTH));
	if (increment_meal_counter(philo))
		return (end_sim(philo, DROP_BOTH));
	return (0);
}

int	eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	if (sim_ended(philo))
		return (0);
	if (eating(philo))
		return (1);
	if (drop_forks(philo, DROP_BOTH))
		return (1);
	return (0);
}

/*
	simulate a philo with a fork. In such case, the philo 
	cannot eat and will die eventually after lapse of 
	time_to_die ms since the start of simulation.
*/

int	eat_alone(t_philo *philo)
{
	if (print_state(TOOK_1ST_FORK, philo))
		return (end_sim(philo, DROP_NONE));
	if (ft_usleep(get_time_to_die(philo->data) + 2000, philo->data))
		return (end_sim(philo, DROP_NONE));
	return (0);
}
