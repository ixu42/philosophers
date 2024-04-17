/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:12:25 by ixu               #+#    #+#             */
/*   Updated: 2024/04/17 17:17:21 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	if philo->id is an even number, the philo starts by thinking before 
	entering while loop so that odd numbered philos can eat first 
	(also works the other way around)
*/

static void	arrange_eating(t_data *data, long time_to_eat)
{
	if (data->id % 2 == 0)
	{
		print_state(THINKING, data);
		ft_usleep(time_to_eat / 2, data);
	}
}

t_bool	sim_should_end(t_data *data)
{
	t_sim_state	sim_state;

	sim_state = get_sim_state(data);
	// printf("%d sim state:%d\n", data->id, sim_state);
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
	long		time_to_eat;
	long		time_to_sleep;
	// pthread_t	monitor_end_sim;

	time_to_eat = get_time_to_eat(data);
	time_to_sleep = get_time_to_sleep(data);
	safe_pthread(CREATE, &monitor, &monitoring, data);
	// safe_pthread(CREATE, &monitor_end_sim, &monitoring_end_sim, data);
	safe_pthread(DETACH, &monitor, NULL, data);
	// safe_pthread(DETACH, &monitor_end_sim, NULL, data);
	arrange_eating(data, time_to_eat);
	while (true)
	{
		// printf("%d in routine while loop\n", data->id);
		// if (sim_should_end(data))
		// {
		// 	// printf("soon to exit...\n");
		// 	// exit(EXIT_SUCCESS);
		// }
		// printf("%d before eating\n", data->id);
		if (data->philo_count == 1)
			eat_alone(data);
		else
			eat(data, time_to_eat);
		// printf("%d after eating\n", data->id);
		// printf("%d meals eaten:%d\n", data->id, data->meals_eaten);
		// if (sim_should_end(data))
		// {
		// 	// printf("%d soon to exit!\n", data->id);
		// 	// exit(EXIT_SUCCESS);
		// }
		print_state(SLEEPING, data);
		ft_usleep(time_to_sleep, data);
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
	int		i;

	data = (t_data *)arg;
	// printf("waiting for a_philo_died sem to signal...\n");
	safe_sem(SEM_WAIT, data->a_philo_died, data);
	data->someone_died = true;
	// safe_sem(SEM_POST, data->end_sim, data);
	// printf("killing all processes\n");
	// if (!data->all_philos_full)
	// {
		i = -1;
		while (++i < data->philo_count)
			kill(data->pids[i], SIGTERM);
			// printf("%d being terminated, kill() returns:%d\n", i + 1, kill(data->pids[i], SIGTERM));
	// }
	return (NULL);
}

static void	*monitoring_full(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	while (++i < data->philo_count && !data->someone_died)
		safe_sem(SEM_WAIT, data->a_philo_full, data);	
	// printf("someone died:%d\n", data->someone_died);
	if (!data->someone_died)
	{
		i = -1;
		while (++i < data->philo_count)
			kill(data->pids[i], SIGTERM);
			// printf("%d being terminated, kill() returns:%d\n", i + 1, kill(data->pids[i], SIGTERM));
	}
	return (NULL);
}

void	simulate(t_data *data)
{
	int		i;
	// pid_t	*pids;
	pthread_t	monitor_death;
	pthread_t	monitor_full;
	int		status;
	// int		full_counter;

	data->pids = (pid_t *)malloc(sizeof(pid_t) * data->philo_count);
	if (data->pids == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		unlink_all_sems();
		exit(EXIT_FAILURE);
	}
	prepare_simulation(data);
	i = -1;
	while (++i < data->philo_count)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
		{
			ft_putstr_fd(ERR_FORK, 2);
			unlink_all_sems();
			free(data->pids);
			exit(EXIT_FAILURE);
		}
		if (data->pids[i] == 0)
		{
			data->id = i + 1;
			// printf("philo %d starting routine...\n", data->id);
			routine(data);
		}
	}
	safe_pthread(CREATE, &monitor_death, &monitoring_death, data);
	safe_pthread(CREATE, &monitor_full, &monitoring_full, data);
	safe_pthread(DETACH, &monitor_death, NULL, data);
	safe_pthread(DETACH, &monitor_full, NULL, data);
	i = -1;
	// full_counter = 0;
	while (++i < data->philo_count)
	{
		if (waitpid(data->pids[i], &status, 0) == -1)
		{
			ft_putstr_fd(ERR_WAITPID, 2);
			unlink_all_sems();
			free(data->pids);
			exit(EXIT_FAILURE);
		}
		// printf("philo %d exiting...\n", i + 1);
		// if (WEXITED)
		// 	full_counter++;
	}
	// if (full_counter == data->philo_count)
	// 	data->all_philos_full = true;
	safe_sem(SEM_POST, data->a_philo_died, data);
	i = -1;
	while (++i < data->philo_count)
		safe_sem(SEM_POST, data->a_philo_full, data);
	// safe_pthread(JOIN, &monitor_death, monitoring_death, data);
	free(data->pids);
}
