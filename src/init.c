/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:17:54 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/02/09 19:04:21 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, t_philo **philos)
{
	data->someone_died = 0;
	data->start_time = get_time();
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (-1);
	}
	if (init_forks(data) == -1)
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		return (-1);
	}
	if (init_philos(data, philos) == -1)
	{
		cleanup(data, NULL);
		return (-1);
	}
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;
	int	j;
	int	result;
	
	data->forks = malloc(data->nb_philos * sizeof(pthread_mutex_t));
	if (data->forks == NULL)
		return (-1);
	i = 0;
	while (i < data->nb_philos)
	{
		result = pthread_mutex_init(&data->forks[i], NULL);
		if (result != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&data->forks[j]);
				j++;
			}
			free(data->forks);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	init_philos(t_data *data, t_philo **philos)
{
	int	i;
	t_philo *philo;
		
	*philos = malloc(data->nb_philos * sizeof(t_philo));
	if (*philos == NULL)
		return (-1);
	i = 0;
	while (i < data->nb_philos)
	{
		philo = &(*philos)[i];
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->last_meal = 0;
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[(i + 1) % data->nb_philos];
		philo->data = data;
		i++;
	}
	return (0);
}

void	cleanup(t_data *data, t_philo *philos)
{
	int	i;
	
	if (data->forks != NULL)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	if (data->forks != NULL)
	{
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	if (philos != NULL)
		free(philos);
}
