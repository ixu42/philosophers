/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:12:25 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 17:07:26 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	clean_exit(char *err_msg, t_data *data)
{
	if (err_msg != NULL)
		ft_putstr_fd(err_msg, 2);
	close_all_sems(data);
	sem_close(data->sem);
	sem_unlink(data->sem_name);
	free(data->sem_name);
	if (err_msg != NULL)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static void	init_philo(t_data *data, int i)
{
	char	*sem_id;

	sem_id = ft_itoa(i);
	if (sem_id == NULL)
	{
		close_all_sems(data);
		exit(EXIT_FAILURE);
	}
	data->sem_name = ft_strjoin("/sem_", sem_id);
	if (data->sem_name == NULL)
	{
		close_all_sems(data);
		exit(EXIT_FAILURE);
	}
	free(sem_id);
	sem_unlink(data->sem_name);
	data->sem = sem_open(data->sem_name, O_CREAT, 0644, 1);
	if (data->sem == SEM_FAILED)
		clean_exit(ERR_SEM_OPEN, data);
	data->id = i + 1;
	sem_wait(data->sem);
	data->last_meal_time = get_time(MICROSEC, data);
	sem_post(data->sem);
}

/*
	if philo->id is an even number, the philo starts by thinking before 
	entering while loop so that odd numbered philos can eat first 
	(also works the other way around).

	as usleep() does not consume CPU resources actively as sem_wait(), it
	works better esp. for large number of philos if the waiting time
	is mostly lapsed during usleep() instead of sem_wait().
*/

static void	arrange_eating(t_data *data, long time_to_eat)
{
	if (data->id % 2 == 0)
	{
		print_state(THINKING, data);
		ft_usleep(time_to_eat - 1000, data);
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

static void	routine(t_data *data, int i)
{
	pthread_t	monitor;
	long		time_to_eat;
	long		time_to_sleep;

	init_philo(data, i);
	time_to_eat = get_time_to_eat(data);
	time_to_sleep = get_time_to_sleep(data);
	arrange_eating(data, time_to_eat);
	safe_pthread(CREATE, &monitor, &monitoring, data);
	while (!sim_should_end(data))
	{
		if (data->philo_count == 1)
			eat_alone(data);
		else
		{
			if (eat(data, time_to_eat))
				break ;
		}
		if (sim_should_end(data))
			break ;
		print_state(SLEEPING, data);
		ft_usleep(time_to_sleep, data);
		print_state(THINKING, data);
	}
	safe_pthread(JOIN, &monitor, NULL, data);
	clean_exit(NULL, data);
}

static int	put_err_and_return(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	return (1);
}

int	simulate(t_data *data)
{
	int		i;
	pid_t	pid;

	data->sim_start_time = get_time(MILLISEC, data);
	i = -1;
	while (++i < data->philo_count)
	{
		pid = fork();
		if (pid == 0)
			routine(data, i);
		else if (pid == -1)
			return (put_err_and_return(ERR_FORK));
	}
	i = -1;
	while (++i < data->philo_count)
	{
		if (waitpid(0, NULL, 0) == -1)
			return (put_err_and_return(ERR_WAITPID));
	}
	return (0);
}
