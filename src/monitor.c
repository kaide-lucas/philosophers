/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:18:54 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/02/12 17:18:09 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_philo_death(t_philo *philo, long current_time)
{
	long	time_since_meal;
	long	timestamp;

	pthread_mutex_lock(&philo->data->death_mutex);
	time_since_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (time_since_meal > philo->data->time_die)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->someone_died = 1;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		timestamp = get_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d died\n", timestamp, philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	return (0);
}

static int	check_all_ate(t_data *data, t_philo *philos)
{
	int	i;

	if (data->nb_meals == -1)
		return (0);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (philos[i].meals_eaten < data->nb_meals)
		{
			pthread_mutex_unlock(&data->death_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->death_mutex);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		i;
	long	current_time;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		current_time = get_time();
		while (i < philos[0].data->nb_philos)
		{
			if (check_philo_death(&philos[i], current_time))
				return (NULL);
			i++;
		}
		if (check_all_ate(philos[0].data, philos))
		{
			pthread_mutex_lock(&philos[0].data->stop_mutex);
			philos[0].data->someone_died = 1;
			pthread_mutex_unlock(&philos[0].data->stop_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
