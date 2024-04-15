/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:34:48 by ixu               #+#    #+#             */
/*   Updated: 2024/04/14 19:07:08 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	increment_meal_counter(t_philo *philo)
{
	safe_sem(SEM_WAIT, philo->data->sem, philo->data);
	philo->meals_eaten++;
	safe_sem(SEM_POST, philo->data->sem, philo->data);
}

void	set_last_meal_time(t_philo *philo)
{
	safe_sem(SEM_WAIT, philo->data->sem, philo->data);
	philo->last_meal_time = get_time(MICROSEC, philo->data);
	safe_sem(SEM_POST, philo->data->sem, philo->data);
}

void	set_end_sim(t_data *data)
{
	safe_sem(SEM_WAIT, data->sem, data);
	data->end_simulation = true;
	safe_sem(SEM_POST, data->sem, data);
}

/*
	1. unlock the locked forks
	2. set the end_simulation flag to true
	3. return 1 to indicate error
*/

// int	end_sim(t_philo *philo, t_fork fork_to_drop)
// {
// 	if (DEBUG_MODE)
// 		return (end_sim_debug(philo, fork_to_drop));
// 	if (fork_to_drop == DROP_FORK_1)
// 		safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data);
// 	else if (fork_to_drop == DROP_FORK_2)
// 		safe_mutex(MUTEX_UNLOCK, philo->second_fork, philo->data);
// 	else if (fork_to_drop == DROP_BOTH)
// 	{
// 		safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data);
// 		safe_mutex(MUTEX_UNLOCK, philo->second_fork, philo->data);
// 	}
// 	safe_sem(SEM_WAIT, &philo->data->sem, philo->data);
// 	philo->data->end_simulation = true;
// 	safe_sem(SEM_POST, &philo->data->sem, philo->data);
// 	return (1);
// }
