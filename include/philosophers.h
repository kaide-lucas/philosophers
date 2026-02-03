/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 23:59:40 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/02/02 15:10:37 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_data
{
	int				nb_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				nb_meals;
	
	long			start_time;
	int				someone_died;
	
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*rigth_fork;
	
	long			last_meal;
	int				meals_eaten;
	
	t_data			*data;
}	t_philo;
