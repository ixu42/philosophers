/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:44:02 by ixu               #+#    #+#             */
/*   Updated: 2024/04/15 15:09:43 by ixu              ###   ########.fr       */
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
	// data->sim_started = sem_open("/sim_started", O_CREAT, 0644, 0);
	// if (data->sim_started == SEM_FAILED)
	// 	handle_sem_open_error();
	// data->sim_ended = sem_open("/sim_ended", O_CREAT, 0644, 0);
	// if (data->sim_ended == SEM_FAILED)
	// 	handle_sem_open_error();
}

/* static char	*get_philo_sem_name(int philo_id)
{
	char	*sem_id;
	char	*sem_name;

	sem_id = ft_itoa(philo_id);
	if (sem_id == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		exit(EXIT_FAILURE);
	}
	sem_name = ft_strjoin("/sem_", sem_id);
	if (sem_name == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		free(sem_id);
		exit(EXIT_FAILURE);
	}
	free(sem_id);
	return (sem_name);
}

static sem_t	*get_philo_sem(int philo_id, t_data *data)
{
	char	*sem_name;
	sem_t	*sem;

	sem_name = get_philo_sem_name(philo_id);
	sem_unlink(sem_name);
	sem = sem_open(sem_name, O_CREAT, 0644, 1);
	if (sem == SEM_FAILED)
	{
		ft_putstr_fd("sem_open error\n", 2);
		safe_sem(SEM_UNLINK, "/forks", data);
		safe_sem(SEM_UNLINK, "/write", data);
		safe_sem(SEM_UNLINK, "/sem", data);
		exit(EXIT_FAILURE);
	}
	free(sem_name);
	return (sem);
} */

/* static t_philo	*init_philos(t_data *data)
{
	t_philo *philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_count);
	if (philos == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		unlink_all_sems();
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < data->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = INT_MAX;
		// philos[i].sem = get_philo_sem(data->philos[i].id, data); // error checking
		philos[i].data = data;
	}
	return (philos);
} */

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
	data->end_simulation = false;
	init_semaphores(data);
	// data->philos = init_philos(data);
}
