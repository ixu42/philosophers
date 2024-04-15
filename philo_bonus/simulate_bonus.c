/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:12:25 by ixu               #+#    #+#             */
/*   Updated: 2024/04/15 16:42:14 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	if philo->id is an even number, the philo starts by thinking before 
	entering while loop so that odd numbered philos can eat first 
	(also works the other way around)
*/

static void	arrange_eating(t_data *data)
{
	if (data->id % 2 == 0)
	{
		print_state(THINKING, data);
		ft_usleep(get_time_to_eat(data) / 2, data);
	}
}

static void	routine(t_data *data)
{
	arrange_eating(data);
	safe_pthread(CREATE, &data->monitor, &monitoring, data);
	while (true)
	{
		// printf("in routine while loop\n");
		if (sim_ended(data))
			break ;
		// printf("before eating\n");
		if (get_philo_count(data) == 1)
			eat_alone(data);
		else
			eat(data);
		// printf("after eating\n");
		if (sim_ended(data))
			break ;
		// printf("before sleeping\n");
		print_state(SLEEPING, data);
		ft_usleep(get_time_to_sleep(data), data);
		print_state(THINKING, data);
	}
	safe_pthread(JOIN, &data->monitor, NULL, data);
	exit(EXIT_SUCCESS);
}

static void	prepare_simulation(t_data *data)
{
	long	sim_start_time_in_usec;
	int		i;

	data->sim_start_time = get_time(MILLISEC, data);
	sim_start_time_in_usec = get_time(MICROSEC, data);
	i = -1;
	while (++i < data->philo_count)
		data->last_meal_time = sim_start_time_in_usec;
}

void	simulate(t_data *data)
{
	int		i;
	pid_t	*pids;

	pids = (pid_t *)malloc(sizeof(pid_t) * data->philo_count);
	if (pids == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		exit(EXIT_FAILURE);
	}
	// printf("before prep\n");
	prepare_simulation(data);
	// printf("after prep\n");
	i = -1;
	while (++i < data->philo_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			ft_putstr_fd(ERR_FORK, 2);
			unlink_all_sems();
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			// printf("philo %d starts routine\n", i);
			data->id = i + 1;
			routine(data);
			// printf("after routine\n");
		}
	}
	i = -1;
	safe_sem(SEM_WAIT, data->a_philo_died, data);
	// printf("someone died!\n");
	i = -1;
	// int	counter = 0;
	while (++i < data->philo_count)
	{
		// counter++;
		// printf("kill returns:%d\n", kill(pids[i], SIGINT));
		kill(pids[i], SIGINT);
	}
	// printf("counter:%d\n", counter);
	while (++i < data->philo_count)
	{
		if (waitpid(pids[i], NULL, 0) == -1)
		{
			ft_putstr_fd(ERR_WAITPID, 2);
			exit(EXIT_FAILURE);
		}
	}
	free(pids);
}
