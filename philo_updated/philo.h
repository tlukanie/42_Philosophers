/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:34:32 by tlukanie          #+#    #+#             */
/*   Updated: 2023/07/23 15:45:11 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_PHILOS	250

typedef enum e_params
{
	PHILO_NB = 1,
	DIE_TIME = 2,
	EAT_TIME = 3,
	SLEEP_TIME = 4,
	MEALS_COUNT = 5
}	t_params;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	TOOK_FORK_1 = 4,
	TOOK_FORK_2 = 5
}	t_status;

typedef struct s_philo	t_philo;

typedef struct s_table
{
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	unsigned int	philos_amount;
	pthread_t		philo_death;
	int				must_eat_count;
	bool			stop_status;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	stop_status_mutex;
	pthread_mutex_t	output_mutex;
	t_philo			**philos;
}	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		fork[2];
	unsigned int		id;
	unsigned int		ate_count;
	pthread_mutex_t		meal_time_mutex;
	time_t				last_meal;
	t_table				*table;
}	t_philo;

bool			check_input(int argc, char **argv);
int				custom_atoi(char *str);
time_t			ms_time(void);
void			*free_table(t_table *table);
void			destroy_mutexes(t_table *table);
t_table			*init_table(int argc, char **argv);
void			*philosopher(void *table_data);
void			sleep_routine(t_table *table, time_t sleep_time);
void			output_message(t_philo *philo, bool died, t_status state);
void			*death_simulation(void *table_data);
bool			stop_flag_status(t_table *table);

#endif