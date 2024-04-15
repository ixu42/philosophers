/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:34:20 by ixu               #+#    #+#             */
/*   Updated: 2024/04/14 20:40:59 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	sim_ended(t_philo *philo)
{
	t_bool	ret;

	safe_sem(SEM_WAIT, philo->data->sem, philo->data);
	ret = philo->data->end_simulation;
	safe_sem(SEM_POST, philo->data->sem, philo->data);
	return (ret);
}

/* t_bool	sim_started(t_data *data)
{
	t_bool	ret;

	printf("debug...0\n");
	safe_sem(SEM_WAIT, data->sem, data);
	printf("debug...1\n");
	ret = data->start_simulation;
	printf("debug...2\n");
	safe_sem(SEM_POST, data->sem, data);
	printf("debug...3\n");
	printf("flag: %d\n", ret);
	return (ret);
} */

long	get_meals_eaten(t_philo *philo)
{
	long	ret;

	safe_sem(SEM_WAIT, philo->data->sem, philo->data);
	ret = philo->meals_eaten;
	safe_sem(SEM_POST, philo->data->sem, philo->data);
	return (ret);
}

long	get_last_meal_time(t_philo *philo)
{
	long	ret;

	safe_sem(SEM_WAIT, philo->data->sem, philo->data);
	ret = philo->last_meal_time;
	safe_sem(SEM_POST, philo->data->sem, philo->data);
	return (ret);
}

long	get_philo_count(t_data *data)
{
	long	ret;

	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->philo_count;
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}

long	get_time_to_eat(t_philo *philo)
{
	long	ret;

	safe_sem(SEM_WAIT, philo->data->sem, philo->data);
	ret = philo->data->time_to_eat;
	safe_sem(SEM_POST, philo->data->sem, philo->data);
	return (ret);
}

long	get_time_to_sleep(t_philo *philo)
{
	long	ret;

	safe_sem(SEM_WAIT, philo->data->sem, philo->data);
	ret = philo->data->time_to_sleep;
	safe_sem(SEM_POST, philo->data->sem, philo->data);
	return (ret);
}

long	get_time_to_die(t_data *data)
{
	long	ret;

	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->time_to_die;
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}
