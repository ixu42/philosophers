/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:34:20 by ixu               #+#    #+#             */
/*   Updated: 2024/04/16 16:27:08 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_sim_state	get_sim_state(t_data *data)
{
	t_sim_state	ret;

	// printf("%d before sem wait for get_sim_state\n", data->id);
	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->sim_state;
	// printf("sim state:%d\n", ret);
	// printf("%d before sem post for get_sim_state\n", data->id);	
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}

long	get_meals_eaten(t_data *data)
{
	long	ret;

	// printf("%d before sem wait for get_meals_eaten\n", data->id);
	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->meals_eaten;
	// printf("%d before sem post for get_meals_eaten\n", data->id);
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}

long	get_last_meal_time(t_data *data)
{
	long	ret;

	// printf("%d before sem wait for get_last_meal_time\n", data->id);
	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->last_meal_time;
	// printf("%d before sem post for get_last_meal_time\n", data->id);
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}

/* long	get_philo_count(t_data *data)
{
	long	ret;

	printf("debug4\n");
	safe_sem(SEM_WAIT, data->sem, data);
	printf("debug5\n");
	ret = data->philo_count;
	printf("debug6\n");
	safe_sem(SEM_POST, data->sem, data);
	printf("debug7\n");
	return (ret);
} */

long	get_time_to_eat(t_data *data)
{
	long	ret;

	// printf("%d before sem wait for get_time_to_eat\n", data->id);
	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->time_to_eat;
	// printf("%d before sem post for get_time_to_eat\n", data->id);
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}

long	get_time_to_sleep(t_data *data)
{
	long	ret;

	// printf("%d before sem wait for get_time_to_sleep\n", data->id);
	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->time_to_sleep;
	// printf("%d before sem post for get_time_to_sleep\n", data->id);
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}

long	get_time_to_die(t_data *data)
{
	long	ret;

	// printf("%d before sem wait for get_time_to_die\n", data->id);
	safe_sem(SEM_WAIT, data->sem, data);
	ret = data->time_to_die;
	// printf("%d before sem post for get_time_to_die\n", data->id);
	safe_sem(SEM_POST, data->sem, data);
	return (ret);
}
