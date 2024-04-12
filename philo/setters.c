/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:30:26 by ixu               #+#    #+#             */
/*   Updated: 2024/04/12 13:28:19 by ixu              ###   ########.fr       */
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

// set the end_simulation flag to true and return 1 to indicate error.

int	end_sim(t_data *data)
{
	safe_mutex(MUTEX_LOCK, &data->mutex, data);
	data->end_simulation = true;
	safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
	return (1);
}
