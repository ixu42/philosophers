/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:07:39 by ixu               #+#    #+#             */
/*   Updated: 2024/04/12 16:48:17 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	if (safe_mutex(MUTEX_LOCK, philo->first_fork, philo->data))
		return (end_sim(philo->data));
	if (sim_ended(philo))
	{
		safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data);
		return (0);
	}
	if (print_state(TOOK_1ST_FORK, philo, DEBUG_MODE))
		return (end_sim(philo->data));
	if (safe_mutex(MUTEX_LOCK, philo->second_fork, philo->data))
		return (end_sim(philo->data));
	if (sim_ended(philo))
	{
		safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data);
		safe_mutex(MUTEX_UNLOCK, philo->second_fork, philo->data);
		return (0);
	}
	if (print_state(TOOK_2ND_FORK, philo, DEBUG_MODE))
		return (end_sim(philo->data));
	return (0);
}

static int	eating(t_philo *philo)
{
	if (set_last_meal_time(philo))
		return (end_sim(philo->data));
	if (print_state(EATING, philo, DEBUG_MODE))
		return (end_sim(philo->data));
	if (ft_usleep(get_time_to_eat(philo), philo->data))
		return (end_sim(philo->data));
	if (increment_meal_counter(philo))
		return (end_sim(philo->data));
	return (0);
}

static int	release_forks(t_philo *philo)
{
	if (safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data))
		return (end_sim(philo->data));
	if (safe_mutex(MUTEX_UNLOCK, philo->second_fork, philo->data))
		return (end_sim(philo->data));
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
	if (release_forks(philo))
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
	if (print_state(TOOK_1ST_FORK, philo, DEBUG_MODE))
		return (end_sim(philo->data));
	if (ft_usleep(get_time_to_die(philo->data), philo->data))
		return (end_sim(philo->data));
	return (0);
}
