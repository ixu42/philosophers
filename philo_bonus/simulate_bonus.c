/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:12:25 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 21:58:14 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	put_err_and_return(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	return (1);
}

int	simulate(t_data *data)
{
	int		i;
	pid_t	pid;

	data->sim_start_time = get_time(MILLISEC);
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
