/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:51:27 by ixu               #+#    #+#             */
/*   Updated: 2024/04/15 15:19:53 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	a_philo_died(t_data *data)
{
	int		i;
	long	time_to_die;
	long	current_time;
	long	last_meal_time;

	i = -1;
	time_to_die = get_time_to_die(data);
	if (get_meals_eaten(data) >= data->meals_limit)
		return (false);
	current_time = get_time(MICROSEC, data);
	last_meal_time = get_last_meal_time(data);
	if (current_time - last_meal_time > time_to_die)
	{
		// printf("current_time:%ld\n", current_time);
		// printf("last_meal_time:%ld\n", last_meal_time);
		// printf("diff:%ld\n", current_time - last_meal_time);
		// printf("time_to_die:%ld\n", time_to_die);
		print_state(DIED, data);
		set_end_sim(data);
		safe_sem(SEM_POST, data->a_philo_died, data);
		return (true);
	}
	return (false);
}

static t_bool	all_philos_full(t_data *data)
{
	int		i;
	long	philo_count;
	long	meals_eaten;

	if (data->meals_limit == INT_MAX)
		return (false);
	i = -1;
	philo_count = get_philo_count(data);
	while (++i < philo_count)
	{
		meals_eaten = get_meals_eaten(data);
		if (meals_eaten < data->meals_limit)
			return (false);
	}
	set_end_sim(data);
	return (true);
}

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (true)
	{
		if (a_philo_died(data) || all_philos_full(data))
			break ;
	}
	return (NULL);
}
