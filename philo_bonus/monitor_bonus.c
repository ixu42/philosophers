/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:51:27 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 17:08:11 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	philo_died(t_data *data, long time_to_die)
{
	long	current_time;
	long	last_meal_time;

	if (get_meals_eaten(data) >= data->meals_limit)
		return (false);
	current_time = get_time(MICROSEC, data);
	last_meal_time = get_last_meal_time(data);
	if (current_time - last_meal_time > time_to_die)
		return (true);
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
	set_sim_state(data, PHILO_FULL);
	return (true);
}

t_bool	someone_died(t_data *data)
{
	sem_t	*death;

	death = sem_open("/death", O_RDONLY, 0);
	if (death == SEM_FAILED)
		return (false);
	safe_sem(SEM_CLOSE, death, data);
	set_sim_state(data, OTHER_PHILO_DIED);
	return (true);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	long	time_to_die;
	sem_t	*death;

	data = (t_data *)arg;
	time_to_die = get_time_to_die(data);
	while (!sim_should_end(data))
	{
		if (someone_died(data))
			break ;
		if (philo_died(data, time_to_die))
		{
			safe_sem(SEM_WAIT, data->write, data);
			if (!someone_died(data))
			{
				death = sem_open("/death", O_CREAT, 0644, 0);
				safe_sem(SEM_CLOSE, death, data);
				set_sim_state(data, PHILO_DIED);
				print_state(DIED, data);
				safe_sem(SEM_POST, data->write, data);
				break ;
			}
			safe_sem(SEM_POST, data->write, data);			
		}
		if (philo_full(data))
			break ;
		ft_usleep(1000, data);
	}
	return (NULL);
}
