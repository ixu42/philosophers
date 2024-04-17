/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:08:29 by ixu               #+#    #+#             */
/*   Updated: 2024/04/17 10:28:09 by ixu              ###   ########.fr       */
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

void	close_all_sems(t_data *data)
{
	safe_sem(SEM_CLOSE, data->forks, data);
	safe_sem(SEM_CLOSE, data->write, data);
	safe_sem(SEM_CLOSE, data->sem, data);
	safe_sem(SEM_CLOSE, data->a_philo_died, data);
	// safe_sem(SEM_CLOSE, data->end_sim, data);
}

void	unlink_all_sems(void)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/sem");
	sem_unlink("/a_philo_died");
	// sem_unlink("/end_sim");
}

static void	clean_all(t_data *data)
{
	close_all_sems(data);
	unlink_all_sems();
}

int	main(int argc, char **argv)
{
	t_data	data;

	// printf("before validate_input()\n");
	validate_input(argc, argv);
	// printf("before init_data()\n");
	init_data(&data, argv);
	// printf("before simulate()\n");
	simulate(&data);
	// printf("before clean_all()\n");
	clean_all(&data);
	// printf("before exit main\n");
	return (0);
}
