/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:51:27 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 21:10:22 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	other_philo_died(t_data *data)
{
	sem_t	*death;

	death = sem_open("/death", O_RDONLY, 0);
	if (death == SEM_FAILED)
		return (false);
	sem_handler(SEM_CLOSE, death);
	set_sim_state(data, OTHER_PHILO_DIED);
	return (true);
}

static t_bool	philo_died(t_data *data, long time_to_die)
{
	long	current_time;
	long	last_meal_time;

	if (get_meals_eaten(data) >= data->meals_limit)
		return (false);
	current_time = get_time(MICROSEC);
	last_meal_time = get_last_meal_time(data);
	if (current_time - last_meal_time > time_to_die)
		return (true);
	return (false);
}

static void	handle_death(t_data *data)
{
	sem_t	*death;

	death = sem_open("/death", O_CREAT, 0644, 0);
	sem_handler(SEM_CLOSE, death);
	set_sim_state(data, PHILO_DIED);
	print_state(DIED, data);
	sem_handler(SEM_POST, data->write);
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

void	*monitoring(void *arg)
{
	t_data	*data;
	long	time_to_die;

	data = (t_data *)arg;
	time_to_die = get_time_to_die(data);
	while (!sim_should_end(data))
	{
		if (other_philo_died(data))
			break ;
		if (philo_died(data, time_to_die))
		{
			sem_handler(SEM_WAIT, data->write);
			if (!other_philo_died(data))
			{
				handle_death(data);
				break ;
			}
			sem_handler(SEM_POST, data->write);
		}
		if (philo_full(data))
			break ;
		ft_usleep(1000);
	}
	return (NULL);
}
