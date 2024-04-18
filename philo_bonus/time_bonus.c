/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:55:35 by ixu               #+#    #+#             */
/*   Updated: 2024/04/18 20:42:44 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// get current time in microseconds or milliseconds

long	get_time(t_time_unit time_unit)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_putstr_fd(ERR_GETTIMEOFDAY, 2);
	if (time_unit == MICROSEC)
		return (tv.tv_sec * 1000000 + tv.tv_usec);
	else if (time_unit == MILLISEC)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (-1);
}

// an improved version of usleep() for better precision

void	ft_usleep(long microsec)
{
	long	start;
	long	current;

	start = get_time(MICROSEC);
	while (true)
	{
		current = get_time(MICROSEC);
		if (current - start >= microsec)
			break ;
		if (usleep(500) == -1)
			ft_putstr_fd(ERR_USLEEP, 2);
	}
}
