/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:29:31 by ixu               #+#    #+#             */
/*   Updated: 2024/04/12 10:56:01 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_philo_count(t_data *data)
{
	long	ret;

	safe_mutex(MUTEX_LOCK, &data->mutex, data);
	ret = data->philo_count;
	safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
	return (ret);
}

long	get_time_to_eat(t_philo *philo)
{
	long	ret;

	safe_mutex(MUTEX_LOCK, &philo->data->mutex, philo->data);
	ret = philo->data->time_to_eat;
	safe_mutex(MUTEX_UNLOCK, &philo->data->mutex, philo->data);
	return (ret);
}

long	get_time_to_sleep(t_philo *philo)
{
	long	ret;

	safe_mutex(MUTEX_LOCK, &philo->data->mutex, philo->data);
	ret = philo->data->time_to_sleep;
	safe_mutex(MUTEX_UNLOCK, &philo->data->mutex, philo->data);
	return (ret);
}

long	get_time_to_die(t_data *data)
{
	long	ret;

	safe_mutex(MUTEX_LOCK, &data->mutex, data);
	ret = data->time_to_die;
	safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
	return (ret);
}
