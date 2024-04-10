/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:07:39 by ixu               #+#    #+#             */
/*   Updated: 2024/04/10 21:06:56 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	if (safe_mutex(MUTEX_LOCK, philo->left_fork, philo->data))
		return (end_sim(philo->data));
	if (philo->data->end_simulation)
	{
		safe_mutex(MUTEX_UNLOCK, philo->left_fork, philo->data);
		return (0);
	}
	if (print_state(TOOK_LEFT_FORK, philo, DEBUG_MODE))
		return (end_sim(philo->data));
	if (safe_mutex(MUTEX_LOCK, philo->right_fork, philo->data))
		return (end_sim(philo->data));
	if (philo->data->end_simulation)
	{
		safe_mutex(MUTEX_UNLOCK, philo->left_fork, philo->data);
		safe_mutex(MUTEX_UNLOCK, philo->right_fork, philo->data);
		return (0);
	}
	if (print_state(TOOK_RIGHT_FORK, philo, DEBUG_MODE))
		return (end_sim(philo->data));
	return (0);
}

static int	eating(t_philo *philo)
{
	if (safe_mutex(MUTEX_LOCK, &philo->mutex, philo->data))
		return (end_sim(philo->data));
	philo->last_meal_time = get_time(MICROSEC, philo->data);
	if (philo->last_meal_time == -1)
		return (end_sim(philo->data));
	if (safe_mutex(MUTEX_UNLOCK, &philo->mutex, philo->data))
		return (end_sim(philo->data));
	if (print_state(EATING, philo, DEBUG_MODE))
		return (end_sim(philo->data));
	if (ft_usleep(philo->data->time_to_eat, philo->data))
		return (end_sim(philo->data));
	if (safe_mutex(MUTEX_LOCK, &philo->mutex, philo->data))
		return (end_sim(philo->data));
	philo->meals_eaten++;
	if (safe_mutex(MUTEX_UNLOCK, &philo->mutex, philo->data))
		return (end_sim(philo->data));
	return (0);
}

static int	release_forks(t_philo *philo)
{
	if (safe_mutex(MUTEX_UNLOCK, philo->left_fork, philo->data))
		return (end_sim(philo->data));
	if (safe_mutex(MUTEX_UNLOCK, philo->right_fork, philo->data))
		return (end_sim(philo->data));
	return (0);
}

int	eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	if (philo->data->end_simulation)
		return (0);
	if (eating(philo))
		return (1);
	if (release_forks(philo))
		return (1);
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
