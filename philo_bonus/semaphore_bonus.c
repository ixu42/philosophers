/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:29:42 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 15:53:21 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	handle_sem_open_error(void)
{
	ft_putstr_fd(ERR_SEM_OPEN, 2);
	unlink_all_sems();
	exit(EXIT_FAILURE);
}

void	init_semaphores(t_data *data)
{
	unlink_all_sems();
	data->forks = sem_open("/forks", O_CREAT, 0644, data->philo_count);
	if (data->forks == SEM_FAILED)
		handle_sem_open_error();
	data->write = sem_open("/write", O_CREAT, 0644, 1);
	if (data->write == SEM_FAILED)
		handle_sem_open_error();
}

void	close_all_sems(t_data *data)
{
	safe_sem(SEM_CLOSE, data->forks, data);
	safe_sem(SEM_CLOSE, data->write, data);
}

void	unlink_all_sems(void)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/death");
}
