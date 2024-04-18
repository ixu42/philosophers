/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:51:27 by ixu               #+#    #+#             */
/*   Updated: 2024/04/16 16:33:54 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	philo_died(t_data *data, long time_to_die)
{
	// long	time_to_die;
	long	current_time;
	long	last_meal_time;

	// time_to_die = get_time_to_die(data); // change in mandatory part as well
	if (get_meals_eaten(data) >= data->meals_limit)
		return (false);
	current_time = get_time(MICROSEC, data);
	last_meal_time = get_last_meal_time(data);
	if (current_time - last_meal_time > time_to_die)
	{
		// printf("current_time:%ld\n", current_time);
		// printf("last_meal_time:%ld\n", last_meal_time / 1000 - data->sim_start_time);
		// printf("id:%d\n", data->id);
		// printf("diff:%ld\n", current_time - last_meal_time);
		// printf("time_to_die:%ld\n", time_to_die);
		// set_sim_state(data, PHILO_DIED);
		// print_state(DIED, data);
		// printf("%d died and signals\n", data->id);
		// safe_sem(SEM_POST, data->a_philo_died, data);
		// printf("%d died and after signaling\n", data->id);
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
	set_sim_state(data, PHILO_FULL);
	// safe_sem(SEM_POST, data->a_philo_full, data);
	// safe_sem(SEM_POST, data->a_philo_died, data);
	return (true);
}

/* void	*monitoring(void *arg)
{
	t_data	*data;
	long	time_to_die;

	data = (t_data *)arg;
	time_to_die = get_time_to_die(data);
	while (true)
	{
		// if (philo_died(data, time_to_die) || philo_full(data))
		// 	break ;
		if (get_sim_state(data) != ACTIVE)
			break ;
		philo_died(data, time_to_die);
		philo_full(data);
	}
	// printf("%d monitor thread terminating...\n", data->id);
	return (NULL);
} */

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
		// printf("checking if someone else died...\n");
		if (someone_died(data))
			break ;
		// printf("checking if the philo died...\n");
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
		// printf("checking if the philo full...\n");
		if (philo_full(data))
			break ;
	}
	// printf("%d monitor thread terminating...\n", data->id);
	return (NULL);
}

/*
	if other philo has died, other_philo_died flag is set to true,
	and the current philo's simulation should end.
*/

/* void	*monitoring_end_sim(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	// printf("%d waiting end_sim...\n", data->id);
	safe_sem(SEM_WAIT, data->end_sim, data);
	if (get_sim_state(data) != PHILO_DIED)
		set_sim_state(data, OTHER_PHILO_DIED);
	// printf("%d signaling end_sim...\n", data->id);
	safe_sem(SEM_POST, data->end_sim, data);
	// printf("%d monitor end sim thread terminating...\n", data->id);
	return (NULL);
} */
