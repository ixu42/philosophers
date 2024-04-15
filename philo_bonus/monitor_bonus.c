/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:51:27 by ixu               #+#    #+#             */
/*   Updated: 2024/04/16 00:10:41 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	philo_died(t_data *data)
{
	long	time_to_die;
	long	current_time;
	long	last_meal_time;

	time_to_die = get_time_to_die(data);
	if (get_meals_eaten(data) >= data->meals_limit)
		return (false);
	current_time = get_time(MICROSEC, data);
	last_meal_time = get_last_meal_time(data);
	if (current_time - last_meal_time > time_to_die)
	{
		// printf("current_time:%ld\n", current_time);
		// printf("last_meal_time:%ld\n", last_meal_time);
		// printf("id:%d\n", data->id);
		// printf("diff:%ld\n", current_time - last_meal_time);
		// printf("time_to_die:%ld\n", time_to_die);
		print_state(DIED, data);
		set_philo_died(data);
		safe_sem(SEM_POST, data->a_philo_died, data);
		return (true);
	}
	return (false);
}

static t_bool	philo_full(t_data *data)
{
	long	meals_eaten;

	if (data->meals_limit == INT_MAX)
		return (false);
	meals_eaten = get_meals_eaten(data);
	if (meals_eaten < data->meals_limit)
		return (false);
	set_philo_full(data);
	return (true);
}

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (true)
	{
		if (philo_died(data) || philo_full(data))
			break ;
	}
	return (NULL);
}

/*
	if other philo has died, other_philo_died flag is set to true,
	and the current philo's simulation should end.
*/

void	*monitoring_end_sim(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	safe_sem(SEM_WAIT, data->end_sim, data);
	set_other_philo_died(data);
	safe_sem(SEM_POST, data->end_sim, data);
	return (NULL);
}
