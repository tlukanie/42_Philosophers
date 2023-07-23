/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:30:37 by tlukanie          #+#    #+#             */
/*   Updated: 2023/07/23 15:36:34 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->philos_amount;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->philos_amount;
		philo->fork[1] = philo->id;
	}
}

static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->philos_amount);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < table->philos_amount)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

static t_philo	**init_philos(t_table *table)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * table->philos_amount);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < table->philos_amount)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (NULL);
		if (pthread_mutex_init(&philos[i]->meal_time_mutex, 0) != 0)
			return (NULL);
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->ate_count = 0;
		set_forks(philos[i]);
		i++;
	}
	return (philos);
}

static bool	init_mutexes(t_table *table)
{
	table->fork_mutexes = init_forks(table);
	if (!table->fork_mutexes)
		return (false);
	if (pthread_mutex_init(&table->stop_status_mutex, 0) != 0)
		return (false);
	if (pthread_mutex_init(&table->output_mutex, 0) != 0)
		return (false);
	return (true);
}

t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (NULL);
	table->philos_amount = custom_atoi(av[PHILO_NB]);
	table->time_to_die = custom_atoi(av[DIE_TIME]);
	table->time_to_eat = custom_atoi(av[EAT_TIME]);
	table->time_to_sleep = custom_atoi(av[SLEEP_TIME]);
	table->must_eat_count = -1;
	if (ac - 1 == 5)
		table->must_eat_count = custom_atoi(av[MEALS_COUNT]);
	table->philos = init_philos(table);
	if (!table->philos)
		return (NULL);
	if (!init_mutexes(table))
		return (NULL);
	table->stop_status = false;
	return (table);
}
