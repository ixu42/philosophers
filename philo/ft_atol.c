/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:38:16 by ixu               #+#    #+#             */
/*   Updated: 2024/04/09 08:34:49 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// converting the value in string to long, meanwhile checking overflow.

static int	convert(int is_neg, long *result, char *str)
{
	if (is_neg == 0)
	{
		*result = *result * 10 + (*str - '0');
		if (*result > INT_MAX)
			return (1);
	}
	else
	{
		*result = *result * 10 - (*str - '0');
		if (*result < INT_MIN)
			return (1);
	}
	return (0);
}

static int	skip_spaces(int *is_neg, char **str)
{
	int	status;

	status = 0;
	while (*(*str) == ' '
		|| (*(*str) >= 9 && *(*str) <= 13))
		(*str)++;
	if (ft_isdigit((*str)[0]) == 0 && ft_isdigit((*str)[1]) == 0)
		status = 1;
	if ((*str)[0] == '-' && ft_isdigit((*str)[1]) == 1)
		*is_neg = 1;
	if ((*str)[0] == '-' || (*str)[0] == '+')
		(*str)++;
	return (status);
}

static int	checks_before_digits(char **str, int *is_neg)
{
	int	status;

	if (ft_strlen(*str) == 0)
		return (1);
	status = skip_spaces(is_neg, str);
	if (status == 1)
		return (1);
	return (0);
}

/*
	Customized implementation of atol() for philosophers project.
	If an error occurs, -1 will be returned by the function.
	An error is deemed to have occurred if (1) the characters 
	preceding the first sequence of numbers (if any) are not valid, 
	(2) overflow has occurred (a value is greater than INT_MAX 
	or less than INT_MIN), or (3) the first sequence of numbers 
	(if any) does not end with '\0'.
*/

long	ft_atol(char *str)
{
	long	result;
	int		is_neg;
	int		status;

	is_neg = 0;
	if (checks_before_digits(&str, &is_neg) == 1)
		return (-1);
	result = 0;
	while (ft_isdigit(*str))
	{
		status = convert(is_neg, &result, str);
		if (status == 1)
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (result);
}
