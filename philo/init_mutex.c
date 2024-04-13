/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:44:13 by ixu               #+#    #+#             */
/*   Updated: 2024/04/13 12:41:40 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_error_and_free_data(t_data *data)
{
	ft_putstr_fd("pthread_mutex_init error\n", 2);
	free(data->philos);
	free(data->forks);
}

static int	init_forks(t_data *data)
{
	int	i;
	int	j;
	int	num_of_forks;

	i = -1;
	num_of_forks = data->philo_count;
	while (++i < num_of_forks)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			j = -1;
			while (++j < i)
				safe_mutex(MUTEX_DESTROY, &data->forks[j], data);
			safe_mutex(MUTEX_DESTROY, &data->mutex, data);
			safe_mutex(MUTEX_DESTROY, &data->write, data);
			put_error_and_free_data(data);
			return (1);
		}
	}
	return (0);
}

static int	init_philo_mutex(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&data->philos[i].mutex, NULL) != 0)
		{
			j = -1;
			while (++j < i)
				safe_mutex(MUTEX_DESTROY, &data->philos[j].mutex, data);
			j = -1;
			while (++j < data->philo_count)
				safe_mutex(MUTEX_DESTROY, &data->forks[j], data);
			safe_mutex(MUTEX_DESTROY, &data->mutex, data);
			safe_mutex(MUTEX_DESTROY, &data->write, data);
			put_error_and_free_data(data);
			return (1);
		}
	}
	return (0);
}

int	init_all_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
	{
		put_error_and_free_data(data);
		return (1);
	}
	if (pthread_mutex_init(&data->write, NULL) != 0)
	{
		safe_mutex(MUTEX_DESTROY, &data->mutex, data);
		put_error_and_free_data(data);
		return (1);
	}
	if (init_forks(data))
		return (1);
	if (init_philo_mutex(data))
		return (1);
	return (0);
}
