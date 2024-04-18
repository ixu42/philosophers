/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:08:29 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 16:56:39 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	validate_input(int argc, char **argv)
{
	int		i;
	char	*err[5];

	err[0] = "Invalid number of philosophers\n";
	err[1] = "Invalid time to die\n";
	err[2] = "Invalid time to eat\n";
	err[3] = "Invalid time to sleep\n";
	err[4] = "Invalid number of times each philosopher must eat\n";
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Invalid number of arguments\n", 2);
		printf(USAGE);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (argv[++i] != NULL)
	{
		if ((i < 5 && ft_atol(argv[i]) <= 0)
			|| (i == 5 && ft_atol(argv[i]) < 0))
		{
			ft_putstr_fd(err[i - 1], 2);
			exit(EXIT_FAILURE);
		}
	}
}

static void	init_data(t_data *data, char **argv)
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
	init_semaphores(data);
}

static void	clean_all(t_data *data)
{
	close_all_sems(data);
	unlink_all_sems();
}

int	main(int argc, char **argv)
{
	t_data	data;

	validate_input(argc, argv);
	init_data(&data, argv);
	if (simulate(&data))
	{
		clean_all(&data);
		return (1);	
	}
	clean_all(&data);
	return (0);
}
