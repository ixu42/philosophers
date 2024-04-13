/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:30:26 by ixu               #+#    #+#             */
/*   Updated: 2024/04/13 14:55:25 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	mutex protection for write operations to prevent data races.
	function calls protected to the extent possible.
*/

int	increment_meal_counter(t_philo *philo)
{
	if (safe_mutex(MUTEX_LOCK, &philo->mutex, philo->data))
		return (1);
	philo->meals_eaten++;
	if (safe_mutex(MUTEX_UNLOCK, &philo->mutex, philo->data))
		return (1);
	return (0);
}

int	set_last_meal_time(t_philo *philo)
{
	if (safe_mutex(MUTEX_LOCK, &philo->mutex, philo->data))
		return (1);
	philo->last_meal_time = get_time(MICROSEC, philo->data);
	if (philo->last_meal_time == -1)
		return (1);
	if (safe_mutex(MUTEX_UNLOCK, &philo->mutex, philo->data))
		return (1);
	return (0);
}

void	set_end_sim(t_data *data)
{
	safe_mutex(MUTEX_LOCK, &data->mutex, data);
	data->end_simulation = true;
	safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
}

/*
	1. unlock the locked forks
	2. set the end_simulation flag to true
	3. return 1 to indicate error
*/

int	end_sim(t_philo *philo, t_fork fork_to_drop)
{
	if (DEBUG_MODE)
		return (end_sim_debug(philo, fork_to_drop));
	if (fork_to_drop == DROP_FORK_1)
		safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data);
	else if (fork_to_drop == DROP_FORK_2)
		safe_mutex(MUTEX_UNLOCK, philo->second_fork, philo->data);
	else if (fork_to_drop == DROP_BOTH)
	{
		safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data);
		safe_mutex(MUTEX_UNLOCK, philo->second_fork, philo->data);
	}
	safe_mutex(MUTEX_LOCK, &philo->data->mutex, philo->data);
	philo->data->end_simulation = true;
	safe_mutex(MUTEX_UNLOCK, &philo->data->mutex, philo->data);
	return (1);
}
