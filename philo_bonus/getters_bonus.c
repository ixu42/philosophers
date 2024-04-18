/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:34:20 by ixu               #+#    #+#             */
/*   Updated: 2024/04/16 16:27:08 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_sim_state	get_sim_state(t_data *data)
{
	t_sim_state	ret;

	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->sim_state;
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}

long	get_meals_eaten(t_data *data)
{
	long	ret;

	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->meals_eaten;
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}

long	get_last_meal_time(t_data *data)
{
	long	ret;

	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->last_meal_time;
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}

long	get_time_to_eat(t_data *data)
{
	long	ret;

	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->time_to_eat;
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}

long	get_time_to_sleep(t_data *data)
{
	long	ret;

	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->time_to_sleep;
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}

long	get_time_to_die(t_data *data)
{
	long	ret;

	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->time_to_die;
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}
