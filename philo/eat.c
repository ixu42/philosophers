/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:07:39 by ixu               #+#    #+#             */
/*   Updated: 2024/04/10 17:30:38 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// set the end_simulation flag to true and return 1 to indicate error.

static int	end_sim(t_data *data)
{
	safe_mutex(MUTEX_LOCK, &data->mutex, data);
	data->end_simulation = true;
	safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
	return (1);
}

static int	prepare_eating(t_philo *philo)
{
	if (safe_mutex(MUTEX_LOCK, philo->left_fork, philo->data))
		return (end_sim(philo->data));
	if (print_state(TOOK_LEFT_FORK, philo, DEBUG_MODE))
		return (end_sim(philo->data));
	if (safe_mutex(MUTEX_LOCK, philo->right_fork, philo->data))
		return (end_sim(philo->data));
	if (print_state(TOOK_RIGHT_FORK, philo, DEBUG_MODE))
		return (end_sim(philo->data));
	if (safe_mutex(MUTEX_LOCK, &philo->mutex, philo->data))
		return (end_sim(philo->data));
	philo->last_meal_time = get_time(MICROSEC, philo->data);
	if (philo->last_meal_time == -1)
		return (end_sim(philo->data));
	if (safe_mutex(MUTEX_UNLOCK, &philo->mutex, philo->data))
		return (end_sim(philo->data));
	return (0);
}

static int	finish_eating(t_philo *philo)
{
	if (safe_mutex(MUTEX_LOCK, &philo->mutex, philo->data))
		return (end_sim(philo->data));
	philo->meals_eaten++;
	if (safe_mutex(MUTEX_UNLOCK, &philo->mutex, philo->data))
		return (end_sim(philo->data));
	if (safe_mutex(MUTEX_UNLOCK, philo->left_fork, philo->data))
		return (end_sim(philo->data));
	if (safe_mutex(MUTEX_UNLOCK, philo->right_fork, philo->data))
		return (end_sim(philo->data));
	return (0);
}

int	eat(t_philo *philo)
{
	if (prepare_eating(philo))
		return (end_sim(philo->data));
	if (print_state(EATING, philo, DEBUG_MODE))
		return (end_sim(philo->data));
	if (ft_usleep(philo->data->time_to_eat, philo->data))
		return (end_sim(philo->data));
	if (finish_eating(philo))
		return (end_sim(philo->data));
	return (0);
}

/*
	simulate a philo with a fork. In such case, the philo 
	cannot eat and will die eventually after lapse of 
	time_to_die ms since the start of simulation.
*/

int	eat_alone(t_philo *philo)
{
	if (print_state(TOOK_LEFT_FORK, philo, DEBUG_MODE))
		return (end_sim(philo->data));
	if (ft_usleep(philo->data->time_to_die, philo->data))
		return (end_sim(philo->data));
	return (0);
}
