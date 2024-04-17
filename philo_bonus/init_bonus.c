/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:44:02 by ixu               #+#    #+#             */
/*   Updated: 2024/04/17 15:58:32 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	handle_sem_open_error(void)
{
	ft_putstr_fd(ERR_SEM_OPEN, 2);
	unlink_all_sems();
	exit(EXIT_FAILURE);
}

static void	init_semaphores(t_data *data)
{
	unlink_all_sems();
	data->forks = sem_open("/forks", O_CREAT, 0644, data->philo_count);
	if (data->forks == SEM_FAILED)
		handle_sem_open_error();
	data->write = sem_open("/write", O_CREAT, 0644, 1);
	if (data->write == SEM_FAILED)
		handle_sem_open_error();
	data->sem = sem_open("/sem", O_CREAT, 0644, 1);
	if (data->sem == SEM_FAILED)
		handle_sem_open_error();
	data->a_philo_died = sem_open("/a_philo_died", O_CREAT, 0644, 0);
	if (data->a_philo_died == SEM_FAILED)
		handle_sem_open_error();
	data->a_philo_full = sem_open("/a_philo_full", O_CREAT, 0644, 0);
	if (data->a_philo_full == SEM_FAILED)
		handle_sem_open_error();
	// data->end_sim = sem_open("/end_sim", O_CREAT, 0644, 0);
	// if (data->end_sim == SEM_FAILED)
	// 	handle_sem_open_error();
}

void	init_data(t_data *data, char **argv)
{
	data->meals_eaten = 0;
	data->last_meal_time = INT_MAX;
	data->philo_count = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5] != NULL)
		data->meals_limit = ft_atol(argv[5]);
	else
		data->meals_limit = INT_MAX;
	data->sim_state = ACTIVE;
	data->someone_died = false;
	init_semaphores(data);
}
