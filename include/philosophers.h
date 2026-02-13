/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 23:59:40 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/02/12 16:51:25 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <string.h>

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
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	*forks;

}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal;
	int				meals_eaten;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	t_data			*data;
}	t_philo;

int		parse_arguments(int argc, char **argv, t_data *data);
void	ft_usleep(long sleep_time);
long	get_time(void);

int		init_data(t_data *data, t_philo **philos);
void	cleanup(t_data *data, t_philo *philos);

void	print_status(t_philo *philo, char *message);
void	take_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

void	*philo_routine(void *arg);

void	*monitor_routine(void *arg);

int		run_simulation(t_data *data, t_philo **philos);

int		main(int argc, char **argv);

#endif
