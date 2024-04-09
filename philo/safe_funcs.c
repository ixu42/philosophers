/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 09:53:05 by ixu               #+#    #+#             */
/*   Updated: 2024/04/09 21:59:02 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_all_mutexes(t_data *data)
{
	int	i;

	safe_mutex(MUTEX_DESTROY, &data->mutex, data);
	i = -1;
	while (++i < data->philo_count)
		safe_mutex(MUTEX_DESTROY, &data->forks[i], data);
	i = -1;
	while (++i < data->philo_count)
		safe_mutex(MUTEX_DESTROY, &data->philos[i].mutex, data);
}

/*
	1. in case of error (err_msg != NULL), print error messages to stderr;
	2. destroy all mutexes in case of successful execution or error other 
	than pthread_mutex_destroy;
	3. free all memory allocated on the heap.
*/

int	safe_exit(char *err_msg, t_data *data, t_func func)
{
	if (err_msg != NULL)
		ft_putstr_fd(err_msg, 2);
	if (err_msg == NULL || func == CREATE || func == JOIN
		|| func == MUTEX_LOCK || func == MUTEX_UNLOCK)
		destroy_all_mutexes(data);
	free(data->philos);
	free(data->forks);
	if (err_msg != NULL)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static void	protect(int status, t_func func, t_data *data)
{
	if (status == 0)
		return ;
	else
	{
		if (func == CREATE)
			safe_exit("pthread_create error\n", data, CREATE);
		else if (func == JOIN)
			safe_exit("pthread_join error\n", data, JOIN);
		else if (func == MUTEX_LOCK)
			safe_exit("pthread_mutex_lock error\n", data, MUTEX_LOCK);
		else if (func == MUTEX_UNLOCK)
			safe_exit("pthread_mutex_unlock error\n", data, MUTEX_UNLOCK);
		else if (func == MUTEX_DESTROY)
			safe_exit("pthread_mutex_destroy error\n", data, MUTEX_DESTROY);
	}
}

/*
	wrapper function for pthread_create and pthread_join, and error handling
	in case pthread_create/pthread_join returns a non-zero value.
*/

void	safe_pthread(t_func func, pthread_t *thread,
		void *(*routine)(void *), void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (func == CREATE)
		protect(pthread_create(thread, NULL, routine, arg), func, philo->data);
	else if (func == JOIN)
		protect(pthread_join(*thread, NULL), func, philo->data);
}

/*
	wrapper function for (1) pthread_mutex_lock, (2) pthread_mutex_unlock, 
	and (3) pthread_mutex_destroy, and error handling in case the above 
	functions returns a non-zero value.
*/

void	safe_mutex(t_func func, t_mutex *mutex, t_data *data)
{
	if (func == MUTEX_LOCK)
		protect(pthread_mutex_lock(mutex), func, data);
	else if (func == MUTEX_UNLOCK)
		protect(pthread_mutex_unlock(mutex), func, data);
	else if (func == MUTEX_DESTROY)
		protect(pthread_mutex_destroy(mutex), func, data);
}
