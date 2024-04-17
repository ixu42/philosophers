/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:17:58 by ixu               #+#    #+#             */
/*   Updated: 2024/04/16 13:49:16 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	1. print error messages to stderr
	2. free all memory allocated on the heap
	(this func is only invoked when func call error occurs)
*/

void	safe_exit(char *err_msg, t_data *data, t_func func)
{
	(void)func; // check this
	(void)data; // check this
	ft_putstr_fd(err_msg, 2);
	// free(data->philos);
	// free(data->forks); // unlink, close sems
	exit (EXIT_FAILURE);
}

static void	protect(int status, t_func func, t_data *data)
{
	if (status != 0)
	{
		if (func == CREATE)
			safe_exit(ERR_CREATE, data, CREATE);
		// else if (func == JOIN)
		// 	safe_exit(ERR_JOIN, data, JOIN);
		else if (func == DETACH)
			safe_exit(ERR_DETACH, data, DETACH);
		else if (func == SEM_WAIT)
			safe_exit(ERR_SEM_WAIT, data, SEM_WAIT);
		else if (func == SEM_POST)
			safe_exit(ERR_SEM_POST, data, SEM_POST);
		else if (func == SEM_CLOSE)
			safe_exit(ERR_SEM_CLOSE, data, SEM_CLOSE);
	}
}

/*
	wrapper function for pthread_create and pthread_join, and error handling
	in case pthread_create/pthread_join returns a non-zero value.
*/

void	safe_pthread(t_func func, pthread_t *thread,
		void *(*routine)(void *), t_data *data)
{
	if (func == CREATE)
		protect(pthread_create(thread, NULL, routine, data), func, data);
	// else if (func == JOIN)
	// 	protect(pthread_join(*thread, NULL), func, data);
	else if (func == DETACH)
		protect(pthread_detach(*thread), func, data);
}

/*
	wrapper function for (1) sem_wait, (2) sem_post, and 
	(3) sem_close, and error handling in case the above 
	functions returns a non-zero value.
*/

void	safe_sem(t_func func, sem_t *sem, t_data *data)
{
	if (func == SEM_WAIT)
		protect(sem_wait(sem), func, data);
	else if (func == SEM_POST)
		protect(sem_post(sem), func, data);
	else if (func == SEM_CLOSE)
		protect(sem_close(sem), func, data);
}
