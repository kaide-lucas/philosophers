/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:58:47 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/02/12 00:08:50 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	create_threads(t_data *data, t_philo *philos, pthread_t *monitor)
{
	int i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, philos) != 0)
		return (-1);
	return (0);
}

static void	join_threads(t_data *data, t_philo *philos, pthread_t monitor)
{
	int i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

int	run_simulation(t_data *data, t_philo **philos)
{
	pthread_t	monitor;

	if (create_threads(data, *philos, &monitor) == -1)
	{
		printf("Error: Thread creation failed\n");
		return (-1);
	}
	join_threads(data, *philos, monitor);
	return (0);
}