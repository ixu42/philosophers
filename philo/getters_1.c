/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:04:27 by ixu               #+#    #+#             */
/*   Updated: 2024/04/12 13:28:43 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	mutex protection for the data read by multiple threads
	to ensure thread safety and prevent potential issues
	related to data consistency in a multithreaded program.

	function calls protected to the extent possible.
*/

t_bool	sim_ended(t_philo *philo)
{
	t_bool	ret;

	safe_mutex(MUTEX_LOCK, &philo->data->mutex, philo->data);
	ret = philo->data->end_simulation;
	safe_mutex(MUTEX_UNLOCK, &philo->data->mutex, philo->data);
	return (ret);
}

t_bool	sim_started(t_data *data)
{
	t_bool	ret;

	safe_mutex(MUTEX_LOCK, &data->mutex, data);
	ret = data->start_simulation;
	safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
	return (ret);
}

long	get_meals_eaten(t_philo *philo)
{
	long	ret;

	if (safe_mutex(MUTEX_LOCK, &philo->mutex, philo->data))
		return (-1);
	ret = philo->meals_eaten;
	if (safe_mutex(MUTEX_UNLOCK, &philo->mutex, philo->data))
		return (-1);
	return (ret);
}

long	get_last_meal_time(t_philo *philo)
{
	long	ret;

	if (safe_mutex(MUTEX_LOCK, &philo->mutex, philo->data))
		return (-1);
	ret = philo->last_meal_time;
	if (safe_mutex(MUTEX_UNLOCK, &philo->mutex, philo->data))
		return (-1);
	return (ret);
}
