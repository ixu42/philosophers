/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:16:09 by ixu               #+#    #+#             */
/*   Updated: 2024/04/12 16:48:47 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// assign forks asymmetrically to avoid deadlocks

static void	assign_forks(t_philo *philos, t_data *data, int i)
{
	int	left_fork_index;
	int	right_fork_index;

	left_fork_index = i;
	right_fork_index = (i - 1 + data->philo_count) % data->philo_count;
	if (i % 2 == 0)
	{
		philos[i].first_fork = &data->forks[left_fork_index];
		philos[i].second_fork = &data->forks[right_fork_index];
	}
	else
	{
		philos[i].first_fork = &data->forks[right_fork_index];
		philos[i].second_fork = &data->forks[left_fork_index];
	}
}

static t_philo	*init_philos(t_data *data)
{
	t_philo	*philos;
	int		philo_count;
	int		i;

	philo_count = data->philo_count;
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
		assign_forks(philos, data, i);
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
	data->philos = init_philos(data);
	if (data->philos == NULL)
		return (1);
	return (0);
}
