/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:03:34 by ixu               #+#    #+#             */
/*   Updated: 2024/04/09 20:46:15 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	safe_mutex(MUTEX_LOCK, philo->left_fork, philo->data);
	print_state(TOOK_LEFT_FORK, philo, DEBUG_MODE);
	safe_mutex(MUTEX_LOCK, philo->right_fork, philo->data);
	print_state(TOOK_RIGHT_FORK, philo, DEBUG_MODE);
	safe_mutex(MUTEX_LOCK, &philo->mutex, philo->data);
	philo->last_meal_time = get_time(MICROSEC, philo->data);
	safe_mutex(MUTEX_UNLOCK, &philo->mutex, philo->data);
	print_state(EATING, philo, DEBUG_MODE);
	ft_usleep(philo->data->time_to_eat, philo->data);
	safe_mutex(MUTEX_LOCK, &philo->mutex, philo->data);
	philo->meals_eaten++;
	safe_mutex(MUTEX_UNLOCK, &philo->mutex, philo->data);
	safe_mutex(MUTEX_UNLOCK, philo->left_fork, philo->data);
	safe_mutex(MUTEX_UNLOCK, philo->right_fork, philo->data);
}

/*
	simulate a philo with a fork. In such case, the philo 
	cannot eat and will die eventually after lapse of 
	time_to_die ms since the start of simulation.
*/

static void	eat_alone(t_philo *philo)
{
	print_state(TOOK_LEFT_FORK, philo, DEBUG_MODE);
	ft_usleep(philo->data->time_to_die, philo->data);
}

/*
	1. all philo threads wait until all threads have been created
	2. arrange which philo to eat first, and which to think first:
	if philo->id is an even number, the philo starts by thinking before 
	entering while loop so that odd numbered philos can eat first 
	(also works the other way around)
	3. unless end_simulatoin flag is set to true by monitor thread, 
	each philo performs routine: eat->sleep->think(wait for their turn to eat)
*/

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->start_simulation)
		;
	if (philo->id % 2 == 1)
	{
		print_state(THINKING, philo, DEBUG_MODE);
		ft_usleep(philo->data->time_to_eat / 2, philo->data);
	}
	while (!philo->data->end_simulation)
	{
		if (philo->data->philo_count == 1)
			eat_alone(philo);
		else
			eat(philo);
		print_state(SLEEPING, philo, DEBUG_MODE);
		ft_usleep(philo->data->time_to_sleep, philo->data);
		print_state(THINKING, philo, DEBUG_MODE);
	}
	return (NULL);
}

/*
	after all threads are created,
	1. set simulation starting time (in ms)
	2. initialize last meal time for each philo
	3. set the start_simulation flag to true
*/

static void	prepare_simulation(t_data *data)
{
	long	sim_start_time_in_usec;
	int		i;

	safe_mutex(MUTEX_LOCK, &data->mutex, data);
	data->sim_start_time = get_time(MILLISEC, data);
	sim_start_time_in_usec = get_time(MICROSEC, data);
	i = -1;
	while (++i < data->philo_count)
		data->philos[i].last_meal_time = sim_start_time_in_usec;
	data->start_simulation = true;
	safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
}

int	create_threads(t_data *data)
{
	int	i;

	init_all_mutexes(data);
	safe_pthread(CREATE, &data->monitor, &monitoring, data);
	i = -1;
	while (++i < data->philo_count)
		safe_pthread(CREATE, &data->philos[i].thread, &routine,
			&data->philos[i]);
	prepare_simulation(data);
	safe_pthread(JOIN, &data->monitor, NULL, data);
	i = -1;
	while (++i < data->philo_count)
		safe_pthread(JOIN, &data->philos[i].thread, NULL, &data->philos[i]);
	return (0);
}
