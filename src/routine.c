/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:18:12 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/02/12 17:18:12 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(1);
}

static int	check_death(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(&philo->data->death_mutex);
	died = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (died);
}

static int	check_meals_done(t_philo *philo)
{
	int	done;

	if (philo->data->nb_meals == -1)
		return (0);
	pthread_mutex_lock(&philo->data->death_mutex);
	done = (philo->meals_eaten >= philo->data->nb_meals);
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (done);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	init_philo_routine(philo);
	if (philo->data->nb_philos == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data->time_die + 1);
		return (NULL);
	}
	while (1)
	{
		if (check_death(philo))
			break ;
		take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (check_meals_done(philo))
			break ;
	}
	return (NULL);
}
