/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:23:01 by ixu               #+#    #+#             */
/*   Updated: 2024/04/14 18:02:37 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static void	get_fork_idx(int *fork1, int *fork2, t_philo *philo)
// {
// 	int	philo_idx;
// 	int	philo_count;

// 	philo_idx = philo->id - 1;
// 	philo_count = get_philo_count(philo->data);
// 	if (philo_idx % 2 == 0)
// 	{
// 		*fork1 = philo_idx;
// 		*fork2 = (philo_idx - 1 + philo_count) % philo_count;
// 	}
// 	else
// 	{
// 		*fork1 = (philo_idx - 1 + philo_count) % philo_count;
// 		*fork2 = philo_idx;
// 	}
// }

// void	print_state_debug(t_state state, t_philo *philo, long time)
// {
// 	int	fork1;
// 	int	fork2;

// 	get_fork_idx(&fork1, &fork2, philo);
// 	if (state == TOOK_1ST_FORK)
// 		printf("%-5ld %d has taken fork[%d]\n", time, philo->id, fork1);
// 	else if (state == TOOK_2ND_FORK)
// 		printf("%-5ld %d has taken fork[%d]\n", time, philo->id, fork2);
// 	else if (state == DROPPED_1ST_FORK)
// 		printf("%-5ld %d has dropped fork[%d]\n", time, philo->id, fork1);
// 	else if (state == DROPPED_2ND_FORK)
// 		printf("%-5ld %d has dropped fork[%d]\n", time, philo->id, fork2);
// 	else if (state == EATING)
// 		printf("%s%-5ld %d is eating%s\n", GREEN, time, philo->id, END);
// 	else if (state == SLEEPING)
// 		printf("%-5ld %d is sleeping\n", time, philo->id);
// 	else if (state == THINKING)
// 		printf("%-5ld %d is thinking\n", time, philo->id);
// 	else if (state == DIED)
// 		printf("%s%-5ld %d died%s\n", RED, time, philo->id, END);
// }

// int	drop_forks_debug(t_philo *philo, t_fork fork_to_drop)
// {
// 	if (fork_to_drop == DROP_FORK_1)
// 	{
// 		if (safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data))
// 			return (end_sim(philo, DROP_NONE));
// 		print_state(DROPPED_1ST_FORK, philo);
// 	}
// 	else if (fork_to_drop == DROP_FORK_2)
// 	{
// 		if (safe_mutex(MUTEX_UNLOCK, philo->second_fork, philo->data))
// 			return (end_sim(philo, DROP_NONE));
// 		print_state(DROPPED_2ND_FORK, philo);
// 	}
// 	else if (fork_to_drop == DROP_BOTH)
// 	{
// 		if (safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data))
// 			return (end_sim(philo, DROP_NONE));
// 		print_state(DROPPED_1ST_FORK, philo);
// 		if (safe_mutex(MUTEX_UNLOCK, philo->second_fork, philo->data))
// 			return (end_sim(philo, DROP_NONE));
// 		print_state(DROPPED_2ND_FORK, philo);
// 	}
// 	return (0);
// }

// int	end_sim_debug(t_philo *philo, t_fork fork_to_drop)
// {
// 	if (fork_to_drop == DROP_FORK_1)
// 	{
// 		safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data);
// 		print_state(DROPPED_1ST_FORK, philo);
// 	}
// 	else if (fork_to_drop == DROP_FORK_2)
// 	{
// 		safe_mutex(MUTEX_UNLOCK, philo->second_fork, philo->data);
// 		print_state(DROPPED_2ND_FORK, philo);
// 	}
// 	else if (fork_to_drop == DROP_BOTH)
// 	{
// 		safe_mutex(MUTEX_UNLOCK, philo->first_fork, philo->data);
// 		print_state(DROPPED_1ST_FORK, philo);
// 		safe_mutex(MUTEX_UNLOCK, philo->second_fork, philo->data);
// 		print_state(DROPPED_2ND_FORK, philo);
// 	}
// 	safe_mutex(MUTEX_LOCK, &philo->data->mutex, philo->data);
// 	philo->data->end_simulation = true;
// 	safe_mutex(MUTEX_UNLOCK, &philo->data->mutex, philo->data);
// 	return (1);
// }
