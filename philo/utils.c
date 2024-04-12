/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:28:52 by ixu               #+#    #+#             */
/*   Updated: 2024/04/11 19:18:41 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
	{
		if (ft_putstr_fd("(null)", fd) == -1)
			return (-1);
		return (0);
	}
	if (write(fd, s, ft_strlen(s)) == -1)
		return (-1);
	return (0);
}

// get current time in microseconds or milliseconds

long	get_time(t_time_unit time_unit, t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		safe_mutex(MUTEX_LOCK, &data->mutex, data);
		return (safe_return("gettimeofday error\n", data, GETTIMEOFDAY));
		safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
	}
	if (time_unit == MICROSEC)
		return (tv.tv_sec * 1000000 + tv.tv_usec);
	else if (time_unit == MILLISEC)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (0);
}

// an improved version of usleep() for better precision

int	ft_usleep(long microsec, t_data *data)
{
	long	start;
	long	current;

	start = get_time(MICROSEC, data);
	if (start == -1)
		return (1);
	while (true)
	{
		current = get_time(MICROSEC, data);
		if (current == -1)
			return (1);
		if (current - start >= microsec)
			break ;
		if (usleep(500) == -1)
		{
			safe_mutex(MUTEX_LOCK, &data->mutex, data);
			return (safe_return("usleep error\n", data, USLEEP));
			safe_mutex(MUTEX_UNLOCK, &data->mutex, data);
		}
	}
	return (0);
}
