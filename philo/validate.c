/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:27:24 by ixu               #+#    #+#             */
/*   Updated: 2024/04/09 08:33:05 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_input(int argc, char **argv)
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
		return (1);
	}
	i = 0;
	while (argv[++i] != NULL)
	{
		if ((i < 5 && ft_atol(argv[i]) <= 0) || \
			(i == 5 && ft_atol(argv[i]) < 0))
		{
			ft_putstr_fd(err[i - 1], 2);
			return (1);
		}
	}
	return (0);
}
