/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:15:38 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/02/12 00:08:20 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;

	philos = NULL;
	if (parse_arguments(argc, argv, &data) == -1)
	{
		printf("ERROR: Invalid arguments\n");
		return (1);
	}
	if (init_data(&data, &philos) == -1)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (run_simulation(&data, &philos) == -1)
	{
		cleanup(&data, philos);
		return (1);
	}
	cleanup(&data, philos);
	return (0);
}
