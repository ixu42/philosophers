/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:45:29 by ixu               #+#    #+#             */
/*   Updated: 2024/04/12 14:00:08 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_flag(t_bool *a_philo_died, t_bool value)
{
	*a_philo_died = value;
	return (1);
}
/*
	check each philo and set a_philo_died flag when certain conditions are met

	return -1: function call error
	return 1: a_philo_died flag is given a value 
				-> no need to check further in the while loop
	return 0: the philo should be continuously checked in the while loop
*/

static int	check(t_data *data, t_philo *philo, t_bool *a_philo_died)
{
	long	current_time;
	long	meals_eaten;
	long	last_meal_time;

	meals_eaten = get_meals_eaten(philo);
	if (meals_eaten == -1)
		return (-1);
	if (meals_eaten >= data->meals_limit)
		return (set_flag(a_philo_died, false));
	current_time = get_time(MICROSEC, data);
	if (current_time == -1)
		return (-1);
	last_meal_time = get_last_meal_time(philo);
	if (last_meal_time == -1)
		return (-1);
	if (current_time - last_meal_time > get_time_to_die(data))
	{
		if (print_state(DIED, philo, DEBUG_MODE))
			return (-1);
		return (set_flag(a_philo_died, true));
	}
	return (0);
}

static int	if_a_philo_died(t_data *data, t_bool *a_philo_died)
{
	int		i;
	int		status;

	i = -1;
	while (++i < get_philo_count(data))
	{
		status = check(data, &data->philos[i], a_philo_died);
		if (status == -1)
			return (1);
		else if (status == 1)
			return (0);
	}
	*a_philo_died = false;
	return (0);
}

static int	if_all_philos_full(t_data *data, t_bool *all_philos_full)
{
	int		i;
	long	meals_eaten;

	if (data->meals_limit == INT_MAX)
	{
		*all_philos_full = false;
		return (0);
	}
	i = -1;
	while (++i < get_philo_count(data))
	{
		meals_eaten = get_meals_eaten(&data->philos[i]);
		if (meals_eaten == -1)
			return (1);
		if (meals_eaten < data->meals_limit)
		{
			*all_philos_full = false;
			return (0);
		}
	}
	*all_philos_full = true;
	return (0);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	t_bool	a_philo_died;
	t_bool	all_philos_full;

	data = (t_data *)arg;
	while (!sim_started(data))
		;
	while (true)
	{
		if (if_a_philo_died(data, &a_philo_died)
			|| if_all_philos_full(data, &all_philos_full))
		{
			set_end_sim(data);
			return (NULL);
		}
		if (a_philo_died || all_philos_full)
		{
			set_end_sim(data);
			break ;
		}
	}
	return (NULL);
}
