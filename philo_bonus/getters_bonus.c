/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:34:20 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 21:54:24 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_sim_state	get_sim_state(t_data *data)
{
	t_sim_state	ret;

	sem_handler(SEM_WAIT, data->sem);
	ret = data->sim_state;
	sem_handler(SEM_POST, data->sem);
	return (ret);
}

long	get_meals_eaten(t_data *data)
{
	long	ret;

	sem_handler(SEM_WAIT, data->sem);
	ret = data->meals_eaten;
	sem_handler(SEM_POST, data->sem);
	return (ret);
}

long	get_last_meal_time(t_data *data)
{
	long	ret;

	sem_handler(SEM_WAIT, data->sem);
	ret = data->last_meal_time;
	sem_handler(SEM_POST, data->sem);
	return (ret);
}

long	get_time_to_die(t_data *data)
{
	long	ret;

	sem_handler(SEM_WAIT, data->sem);
	ret = data->time_to_die;
	sem_handler(SEM_POST, data->sem);
	return (ret);
}
