/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:18:12 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/02/10 19:10:56 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	
}

void	print_status(t_philo *philo, char *message)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->data->someone_died == 1)
	{
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	timestamp = get_time() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(philo->print_mutex);
}

