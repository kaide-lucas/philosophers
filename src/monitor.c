/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:18:54 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/02/11 21:34:33 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int check_philo_death(t_philo *philo, long current_time)
{
    long    time_since_meal;

    pthread_mutex_lock(&philo->data->death_mutex);
    time_since_meal = current_time - philo->last_meal;
    if (time_since_meal > philo->data->time_die)
    {
        philo->data->someone_died = 1;
        pthread_mutex_unlock(&philo->data->death_mutex);
        print_status(philo, "died");
        return (1);
    }
    pthread_mutex_unlock(&philo->data->death_mutex);
    return (0);
}

static int check_all_ate(t_data *data, t_philo *philos)
{
    int i;

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

void    *monitor_routine(void *arg)
{
    t_philo *philos;
    int     i;
    long    current_time;

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
            pthread_mutex_lock(&philos[0].data->death_mutex);
            philos[0].data->someone_died = 1;
            pthread_mutex_unlock(&philos[0].data->death_mutex);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}