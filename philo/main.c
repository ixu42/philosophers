/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:06:58 by ixu               #+#    #+#             */
/*   Updated: 2024/04/09 16:55:06 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate_input(argc, argv) == 1)
		return (1);
	init_data(&data, argv);
	create_threads(&data);
	safe_exit(NULL, &data, SUCCESS);
}
