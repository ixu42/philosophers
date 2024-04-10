/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:45:29 by ixu               #+#    #+#             */
/*   Updated: 2024/04/10 17:54:49 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	if_a_philo_died(t_data *data, t_bool *a_philo_died)
{
	int		i;
	long	current_time;

	i = -1;
	while (++i < data->philo_count)
	{
		if (data->philos[i].meals_eaten >= data->meals_limit)
		{
			*a_philo_died = false;
			return (0);
		}
		current_time = get_time(MICROSEC, data);
		if (current_time == -1)
			return (1);
		if (current_time - data->philos[i].last_meal_time > data->time_to_die)
		{
			if (print_state(DIED, &data->philos[i], DEBUG_MODE))
				return (1);
			*a_philo_died = true;
			return (0);
		}
	}
	*a_philo_died = false;
	return (0);
}

static t_bool	all_philos_full(t_data *data)
{
	int	i;

	if (data->meals_limit == INT_MAX)
		return (false);
	i = -1;
	while (++i < data->philo_count)
	{
		if (data->philos[i].meals_eaten < data->meals_limit)
			return (false);
	}
	return (true);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	t_bool	a_philo_died;

	data = (t_data *)arg;
	while (!data->start_simulation)
		;
	while (true)
	{
		if (if_a_philo_died(data, &a_philo_died))
		{
			safe_mutex(MUTEX_LOCK, &data->mutex, data);
			data->end_simulation = true;
			safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
			return (NULL);
		}
		if (a_philo_died || all_philos_full(data))
		{
			safe_mutex(MUTEX_LOCK, &data->mutex, data);
			data->end_simulation = true;
			safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
			break ;
		}
	}
	return (NULL);
}
