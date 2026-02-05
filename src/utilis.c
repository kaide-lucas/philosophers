/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:20:17 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/02/05 18:40:19 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_valid_number(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol(char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

static long	validate_and_convert(char *arg)
{
	long	num;

	if (!is_valid_number(arg))
		return (-1);
	num = ft_atol(arg);
	if (num <= 0 || num > INT_MAX)
		return (-1);
	return (num);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	long	temp;

	if (argc != 5 && argc != 6)
		return (-1);
	temp = validate_and_convert(argv[1]);
	if (temp == -1)
		return (-1);
	data->nb_philos = (int)temp;
	if ((data->time_die = validate_and_convert(argv[2])) == -1)
		return (-1);
	if ((data->time_eat = validate_and_convert(argv[3])) == -1)
		return (-1);
	if ((data->time_sleep = validate_and_convert(argv[4])) == -1)
		return (-1);
	if (argc == 6)
	{
		temp = validate_and_convert(argv[5]);
		if (temp == -1)
			return (-1);
		data->nb_meals = (int)temp;
		return (0);
	}
	data->nb_meals = -1;
	return (0);
}
