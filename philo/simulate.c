/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:03:34 by ixu               #+#    #+#             */
/*   Updated: 2024/04/10 21:07:09 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// set the end_simulation flag to true and return 1 to indicate error.

int	end_sim(t_data *data)
{
	safe_mutex(MUTEX_LOCK, &data->mutex, data);
	data->end_simulation = true;
	safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
	return (1);
}

/*
	if philo->id is an even number, the philo starts by thinking before 
	entering while loop so that odd numbered philos can eat first 
	(also works the other way around)
*/

static int	arrange_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (print_state(THINKING, philo, DEBUG_MODE))
			return (1);
		if (ft_usleep(philo->data->time_to_eat / 2, philo->data))
			return (1);
	}
	return (0);
}

/*
	1. all philo threads wait until all threads have been created
	2. arrange which philo to eat first, and which to think first
	3. unless end_simulatoin flag is set to true by monitor thread, 
	each philo performs routine: eat->sleep->think(wait for their turn to eat)
*/

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->start_simulation)
		;
	if (arrange_eating(philo))
		return (NULL);
	while (!philo->data->end_simulation)
	{
		if (philo->data->philo_count == 1)
			eat_alone(philo);
		else
			eat(philo);
		if (philo->data->end_simulation)
			break ;
		if (print_state(SLEEPING, philo, DEBUG_MODE))
			break ;
		if (ft_usleep(philo->data->time_to_sleep, philo->data))
			break ;
		if (print_state(THINKING, philo, DEBUG_MODE))
			break ;
	}
	return (NULL);
}

/*
	after all threads are created,
	1. set simulation starting time (in ms)
	2. initialize last meal time for each philo
	3. set the start_simulation flag to true
*/

static int	prepare_simulation(t_data *data)
{
	long	sim_start_time_in_usec;
	int		i;

	if (safe_mutex(MUTEX_LOCK, &data->mutex, data))
		return (1);
	data->sim_start_time = get_time(MILLISEC, data);
	sim_start_time_in_usec = get_time(MICROSEC, data);
	i = -1;
	while (++i < data->philo_count)
		data->philos[i].last_meal_time = sim_start_time_in_usec;
	data->start_simulation = true;
	if (safe_mutex(MUTEX_UNLOCK, &data->mutex, data))
		return (1);
	return (0);
}

int	simulate(t_data *data)
{
	int	i;

	if (init_all_mutexes(data))
		return (1);
	if (safe_pthread(CREATE, &data->monitor, &monitoring, data))
		return (1);
	i = -1;
	while (++i < data->philo_count)
	{
		if (safe_pthread(CREATE, &data->philos[i].thread, &routine,
				&data->philos[i]))
			return (1);
	}
	if (prepare_simulation(data))
		return (1);
	if (safe_pthread(JOIN, &data->monitor, NULL, data))
		return (1);
	i = -1;
	while (++i < data->philo_count)
	{
		if (safe_pthread(JOIN, &data->philos[i].thread, NULL, &data->philos[i]))
			return (1);
	}
	return (0);
}
