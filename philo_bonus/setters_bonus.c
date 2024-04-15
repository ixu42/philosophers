/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:34:48 by ixu               #+#    #+#             */
/*   Updated: 2024/04/16 00:30:06 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	increment_meal_counter(t_data *data)
{
	safe_sem(SEM_WAIT, data->sem, data);
	data->meals_eaten++;
	safe_sem(SEM_POST, data->sem, data);
}

void	set_last_meal_time(t_data *data)
{
	safe_sem(SEM_WAIT, data->sem, data);
	data->last_meal_time = get_time(MICROSEC, data);
	safe_sem(SEM_POST, data->sem, data);
}

void	set_philo_died(t_data *data)
{
	safe_sem(SEM_WAIT, data->sem, data);
	data->sim_state = PHILO_DIED;
	safe_sem(SEM_POST, data->sem, data);
}

void	set_philo_full(t_data *data)
{
	safe_sem(SEM_WAIT, data->sem, data);
	data->sim_state = PHILO_FULL;
	safe_sem(SEM_POST, data->sem, data);
}

void	set_other_philo_died(t_data *data)
{
	safe_sem(SEM_WAIT, data->sem, data);
	data->sim_state = OTHER_PHILO_DIED;
	safe_sem(SEM_POST, data->sem, data);
}
