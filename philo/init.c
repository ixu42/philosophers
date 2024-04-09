/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:16:09 by ixu               #+#    #+#             */
/*   Updated: 2024/04/09 10:44:47 by ixu              ###   ########.fr       */
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
		exit(EXIT_FAILURE);
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

void	init_data(t_data *data, char **argv)
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
		exit(EXIT_FAILURE);
	}
	data->philos = init_philos(argv, data);
}

static void	safe_exit_for_mutex_init(t_data *data)
{
	ft_putstr_fd("pthread_mutex_init error\n", 2);
	free(data->philos);
	free(data->forks);
	exit(EXIT_FAILURE);
}

static void	init_forks(t_data *data)
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
			safe_exit_for_mutex_init(data);
		}
	}
}

void	init_all_mutexes(t_data *data)
{
	int	i;
	int	j;

	if (pthread_mutex_init(&data->mutex, NULL) != 0)
		safe_exit_for_mutex_init(data);
	init_forks(data);
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&data->philos[i].mutex, NULL) != 0)
		{
			j = -1;
			while (++j < i)
				safe_mutex(MUTEX_DESTROY, &data->philos[i].mutex, data);
			safe_exit_for_mutex_init(data);
		}
	}
}
