/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:29:42 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 21:34:20 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_data *data)
{
	unlink_all_sems();
	data->forks = sem_open("/forks", O_CREAT, 0644, data->philo_count);
	if (data->forks == SEM_FAILED)
	{
		ft_putstr_fd(ERR_SEM_OPEN, 2);
		exit(EXIT_FAILURE);
	}
	data->write = sem_open("/write", O_CREAT, 0644, 1);
	if (data->write == SEM_FAILED)
	{
		ft_putstr_fd(ERR_SEM_OPEN, 2);
		sem_handler(SEM_CLOSE, data->forks);
		sem_unlink("/forks");
		exit(EXIT_FAILURE);
	}
}

void	close_all_sems(t_data *data)
{
	sem_handler(SEM_CLOSE, data->forks);
	sem_handler(SEM_CLOSE, data->write);
}

void	unlink_all_sems(void)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/death");
}

// only for debugging purpose

void	sem_handler(t_func func, sem_t *sem)
{
	if (func == SEM_WAIT)
	{
		if (sem_wait(sem) == -1)
			ft_putstr_fd(ERR_SEM_WAIT, 2);
	}
	else if (func == SEM_POST)
	{
		if (sem_post(sem) == -1)
			ft_putstr_fd(ERR_SEM_POST, 2);
	}
	else if (func == SEM_CLOSE)
	{
		if (sem_close(sem) == -1)
			ft_putstr_fd(ERR_SEM_CLOSE, 2);
	}
}
