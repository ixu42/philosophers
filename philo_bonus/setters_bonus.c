/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:34:48 by ixu               #+#    #+#             */
/*   Updated: 2024/04/16 16:23:49 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_last_meal_time(t_data *data)
{
	sem_handler(SEM_WAIT, data->sem);
	data->last_meal_time = get_time(MICROSEC);
	sem_handler(SEM_POST, data->sem);
}

void	increment_meal_counter(t_data *data)
{
	sem_handler(SEM_WAIT, data->sem);
	data->meals_eaten++;
	sem_handler(SEM_POST, data->sem);
}

void	set_sim_state(t_data *data, t_sim_state sim_state)
{
	sem_handler(SEM_WAIT, data->sem);
	data->sim_state = sim_state;
	sem_handler(SEM_POST, data->sem);
}
