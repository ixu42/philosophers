/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:45:29 by ixu               #+#    #+#             */
/*   Updated: 2024/04/09 16:07:37 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	a_philo_died(t_data *data)
{
	int		i;
	long	lapsed;

	i = -1;
	while (++i < data->philo_count)
	{
		if (data->philos[i].meals_eaten >= data->meals_limit)
			return (false);
		lapsed = get_time(MICROSEC, data) - data->philos[i].last_meal_time;
		if (lapsed > data->time_to_die)
		{
			print_state(DIED, &data->philos[i], DEBUG_MODE);
			return (true);
		}
	}
	return (false);
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

	data = (t_data *)arg;
	while (!data->start_simulation)
		;
	while (true)
	{
		if (a_philo_died(data) || all_philos_full(data))
		{
			safe_mutex(MUTEX_LOCK, &data->mutex, data);
			data->end_simulation = true;
			safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
			break ;
		}
	}
	return (NULL);
}
