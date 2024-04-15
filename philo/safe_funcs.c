/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 09:53:05 by ixu               #+#    #+#             */
/*   Updated: 2024/04/15 00:22:04 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_all_mutexes(t_data *data)
{
	int	i;

	if (safe_mutex(MUTEX_DESTROY, &data->mutex, data))
		return (1);
	if (safe_mutex(MUTEX_DESTROY, &data->write, data))
		return (1);
	i = -1;
	while (++i < data->philo_count)
	{
		if (safe_mutex(MUTEX_DESTROY, &data->forks[i], data))
			return (1);
	}
	i = -1;
	while (++i < data->philo_count)
	{
		if (safe_mutex(MUTEX_DESTROY, &data->philos[i].mutex, data))
			return (1);
	}
	return (0);
}

/*
	1. print error messages to stderr
	2. destroy all mutexes in certain cases
	3. free all memory allocated on the heap
	(this func is only invoked when func call error occurs)
*/

int	safe_return(char *err_msg, t_data *data, t_func func)
{
	ft_putstr_fd(err_msg, 2);
	if (func == CREATE || func == JOIN
		|| func == MUTEX_LOCK || func == MUTEX_UNLOCK)
	{
		if (destroy_all_mutexes(data))
			return (1);
	}
	free(data->philos);
	free(data->forks);
	if (func == GETTIMEOFDAY)
		return (-1);
	return (1);
}

static int	protect(int status, t_func func, t_data *data)
{
	if (status == 0)
		return (0);
	else
	{
		if (func == CREATE)
			return (safe_return(ERR_CREATE, data, CREATE));
		else if (func == JOIN)
			return (safe_return(ERR_JOIN, data, JOIN));
		else if (func == MUTEX_LOCK)
			return (safe_return(ERR_MUTEX_LOCK, data, MUTEX_LOCK));
		else if (func == MUTEX_UNLOCK)
			return (safe_return(ERR_MUTEX_UNLOCK, data, MUTEX_UNLOCK));
		else if (func == MUTEX_DESTROY)
			return (safe_return(ERR_MUTEX_DESTROY, data, MUTEX_DESTROY));
	}
	return (1);
}

/*
	wrapper function for pthread_create and pthread_join, and error handling
	in case pthread_create/pthread_join returns a non-zero value.
*/

int	safe_pthread(t_func func, pthread_t *thread,
		void *(*routine)(void *), void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (func == CREATE)
	{
		if (protect(pthread_create(thread, NULL, routine, arg),
				func, philo->data))
			return (1);
	}
	else if (func == JOIN)
	{
		if (protect(pthread_join(*thread, NULL), func, philo->data))
			return (1);
	}
	return (0);
}

/*
	wrapper function for (1) pthread_mutex_lock, (2) pthread_mutex_unlock, 
	and (3) pthread_mutex_destroy, and error handling in case the above 
	functions returns a non-zero value.
*/

int	safe_mutex(t_func func, t_mutex *mutex, t_data *data)
{
	if (func == MUTEX_LOCK)
	{
		if (protect(pthread_mutex_lock(mutex), func, data))
			return (1);
	}
	else if (func == MUTEX_UNLOCK)
	{
		if (protect(pthread_mutex_unlock(mutex), func, data))
			return (1);
	}
	else if (func == MUTEX_DESTROY)
	{
		if (protect(pthread_mutex_destroy(mutex), func, data))
			return (1);
	}
	return (0);
}
