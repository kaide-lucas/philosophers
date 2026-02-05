/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:15:38 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/02/05 18:57:13 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(argc, argv, &data) == -1)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	printf("✅ Arguments parsed successfully!\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("Number of philosophers: %d\n", data.nb_philos);
	printf("Time to die:            %ld ms\n", data.time_die);
	printf("Time to eat:            %ld ms\n", data.time_eat);
	printf("Time to sleep:          %ld ms\n", data.time_sleep);
	if (data.nb_meals == -1)
		printf("Number of meals:        unlimited\n");
	else
		printf("Number of meals:        %d\n", data.nb_meals);
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	return (0);
}

