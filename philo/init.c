/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:16:09 by ixu               #+#    #+#             */
/*   Updated: 2024/04/12 14:16:10 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*init_philos(char **argv, t_data *data)
{
	t_philo	*philos;
	int		philo_count;
	int		i;
	int		right_fork_index;

	philo_count = ft_atol(argv[1]);
	philos = (t_philo *)malloc(sizeof(t_philo) * philo_count);
	if (philos == NULL)
	{
		ft_putstr_fd("malloc error\n", 2);
		free(data->forks);
		return (NULL);
	}
	i = -1;
	while (++i < philo_count)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].left_fork = &data->forks[i];
		right_fork_index = (i - 1 + philo_count) % philo_count;
		philos[i].right_fork = &data->forks[right_fork_index];
		philos[i].data = data;
	}
	return (philos);
}

int	init_data(t_data *data, char **argv)
{
	int	num_of_forks;

	data->philo_count = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5] != NULL)
		data->meals_limit = ft_atol(argv[5]);
	else
		data->meals_limit = INT_MAX;
	data->start_simulation = false;
	data->end_simulation = false;
	num_of_forks = data->philo_count;
	data->forks = (t_mutex *)malloc(sizeof(t_mutex) * num_of_forks);
	if (data->forks == NULL)
	{
		ft_putstr_fd("malloc error\n", 2);
		return (1);
	}
	data->philos = init_philos(argv, data);
	if (data->philos == NULL)
		return (1);
	return (0);
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
			ft_putstr_fd("pthread_mutex_init error\n", 2);
			free(data->philos);
			free(data->forks);
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
			ft_putstr_fd("pthread_mutex_init error\n", 2);
			free(data->philos);
			free(data->forks);
			return (1);
		}
	}
	return (0);
}

int	init_all_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
	{
		ft_putstr_fd("pthread_mutex_init error\n", 2);
		free(data->philos);
		free(data->forks);
		return (1);
	}
	if (pthread_mutex_init(&data->write, NULL) != 0)
	{
		safe_mutex(MUTEX_DESTROY, &data->mutex, data);
		ft_putstr_fd("pthread_mutex_init error\n", 2);
		free(data->philos);
		free(data->forks);
		return (1);
	}
	if (init_forks(data))
		return (1);
	if (init_philo_mutex(data))
		return (1);
	return (0);
}
