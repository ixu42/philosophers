/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:12:25 by ixu               #+#    #+#             */
/*   Updated: 2024/04/15 00:29:31 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	if philo->id is an even number, the philo starts by thinking before 
	entering while loop so that odd numbered philos can eat first 
	(also works the other way around)
*/

static void	arrange_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		print_state(THINKING, philo);
		ft_usleep(get_time_to_eat(philo) / 2, philo->data);
	}
}

static void	routine(t_philo *philo)
{
	arrange_eating(philo);
	safe_pthread(CREATE, &philo->data->monitor, &monitoring, philo->data);
	while (true)
	{
		// printf("in routine while loop\n");
		if (sim_ended(philo))
			break ;
		// printf("before eating\n");
		if (get_philo_count(philo->data) == 1)
			eat_alone(philo);
		else
			eat(philo);
		// printf("after eating\n");
		if (sim_ended(philo))
			break ;
		// printf("before sleeping\n");
		print_state(SLEEPING, philo);
		ft_usleep(get_time_to_sleep(philo), philo->data);
		print_state(THINKING, philo);
	}
	safe_pthread(JOIN, &philo->data->monitor, NULL, philo->data);
	exit(EXIT_SUCCESS);
}

static void	prepare_simulation(t_data *data)
{
	long	sim_start_time_in_usec;
	int		i;

	safe_sem(SEM_WAIT, data->sem, data);
	data->sim_start_time = get_time(MILLISEC, data);
	sim_start_time_in_usec = get_time(MICROSEC, data);
	i = -1;
	while (++i < data->philo_count)
		data->philos[i].last_meal_time = sim_start_time_in_usec;
	safe_sem(SEM_POST, data->sem, data);
}

void	simulate(t_data *data)
{
	int	i;

	// printf("before prep\n");
	prepare_simulation(data);
	// printf("after prep\n");
	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
		{
			ft_putstr_fd(ERR_FORK, 2);
			unlink_all_sems();
			exit(EXIT_FAILURE);
		}
		if (data->philos[i].pid == 0)
		{
			// printf("philo %d starts routine\n", i);
			routine(&data->philos[i]);
			// printf("after routine\n");
		}
	}
	i = -1;
	while (++i < data->philo_count)
	{
		if (waitpid(data->philos[i].pid, NULL, 0) == -1)
		{
			ft_putstr_fd(ERR_WAITPID, 2);
			exit(EXIT_FAILURE);
		}
	}
}
