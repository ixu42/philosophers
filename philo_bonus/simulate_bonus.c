/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:12:25 by ixu               #+#    #+#             */
/*   Updated: 2024/04/16 09:56:56 by ixu              ###   ########.fr       */
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

t_bool	sim_should_end(t_data *data)
{
	t_sim_state	sim_state;

	sim_state = get_sim_state(data);
	if (sim_state == PHILO_DIED)
		return (true);
	else if (sim_state == PHILO_FULL)
		return (true);
	else if (sim_state == OTHER_PHILO_DIED)
		return (true);
	return (false);
}

static void	routine(t_data *data)
{
	pthread_t	monitor;
	pthread_t	monitor_end_sim;

	safe_pthread(CREATE, &monitor, &monitoring, data);
	safe_pthread(CREATE, &monitor_end_sim, &monitoring_end_sim, data);
	safe_pthread(DETACH, &monitor, NULL, data);
	safe_pthread(DETACH, &monitor_end_sim, NULL, data);
	arrange_eating(data);
	while (true)
	{
		// printf("in routine while loop\n");
		if (sim_should_end(data))
			exit(EXIT_SUCCESS);
		// printf("before eating\n");
		if (data->philo_count == 1)
			eat_alone(data);
		else
			eat(data);
		// printf("%d after eating\n", data->id);
		// printf("%d meals eaten:%d\n", data->id, data->meals_eaten);
		// printf("%d has sim ended:%d\n", data->id, data->end_simulation);
		if (sim_should_end(data))
			exit(EXIT_SUCCESS);
		print_state(SLEEPING, data);
		ft_usleep(get_time_to_sleep(data), data);
		print_state(THINKING, data);
	}
	// safe_pthread(JOIN, &monitor, NULL, data);
	// safe_pthread(JOIN, &monitor_end_sim, NULL, data);
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

static void	*monitoring_death(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	safe_sem(SEM_WAIT, data->a_philo_died, data);
	safe_sem(SEM_POST, data->end_sim, data);
	return (NULL);
}

void	simulate(t_data *data)
{
	int		i;
	pid_t	*pids;
	pthread_t	monitor_death;

	pids = (pid_t *)malloc(sizeof(pid_t) * data->philo_count);
	if (pids == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		unlink_all_sems();
		exit(EXIT_FAILURE);
	}
	prepare_simulation(data);
	// safe_pthread(CREATE, &monitor_death, &monitoring_death, data);
	i = -1;
	while (++i < data->philo_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			ft_putstr_fd(ERR_FORK, 2);
			unlink_all_sems();
			free(pids);
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			data->id = i + 1;
			routine(data);
		}
	}
	safe_pthread(CREATE, &monitor_death, &monitoring_death, data);
	safe_pthread(DETACH, &monitor_death, NULL, data);
	i = -1;
	while (++i < data->philo_count)
	{
		if (waitpid(pids[i], NULL, 0) == -1)
		{
			ft_putstr_fd(ERR_WAITPID, 2);
			unlink_all_sems();
			free(pids);
			exit(EXIT_FAILURE);
		}
	}
	safe_sem(SEM_POST, data->a_philo_died, data);
	// safe_pthread(JOIN, &monitor_death, monitoring_death, data);
	free(pids);
}