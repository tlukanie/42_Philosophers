/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:33:54 by tlukanie          #+#    #+#             */
/*   Updated: 2023/07/23 16:09:31 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	output_message(t_philo *philo, bool died, t_status state)
{
	pthread_mutex_lock(&philo->table->output_mutex);
	if (stop_flag_status(philo->table) == true && died == false)
	{
		pthread_mutex_unlock(&philo->table->output_mutex);
		return ;
	}
	if (state == DIED)
		printf("%ld %d %s\n", ms_time() - philo->table->start_time,
			philo->id + 1, "\033[1;5;91;40m died \033[0m");
	else if (state == EATING)
		printf("%ld %d %s\n", ms_time() - philo->table->start_time,
			philo->id + 1, "\033[92m is eating \033[0m");
	else if (state == SLEEPING)
		printf("%ld %d %s\n", ms_time() - philo->table->start_time,
			philo->id + 1, "\033[36mis sleeping\033[0m");
	else if (state == THINKING)
		printf("%ld %d %s\n", ms_time() - philo->table->start_time,
			philo->id + 1, "\033[95mis thinking\033[0m");
	else if (state == TOOK_FORK_1 || state == TOOK_FORK_2)
		printf("%ld %d %s\n", ms_time() - philo->table->start_time,
			philo->id + 1, "\033[90mhas taken a fork\033[0m");
	pthread_mutex_unlock(&philo->table->output_mutex);
}

time_t	ms_time(void)
{
	struct timeval	tv;
	time_t			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (ms);
}

static bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->start_time = ms_time() + (table->philos_amount * 2 * 10);
	i = 0;
	while (i < table->philos_amount)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				&philosopher, table->philos[i]) != 0)
			return (false);
		i++;
	}
	if (table->philos_amount > 1)
	{
		if (pthread_create(&table->philo_death, NULL,
				&death_simulation, table) != 0)
			return (false);
	}
	return (true);
}

static void	stop_simulation(t_table	*table)
{
	unsigned int	i;

	i = 0;
	while (i < table->philos_amount)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	if (table->philos_amount > 1)
		pthread_join(table->philo_death, NULL);
	destroy_mutexes(table);
	free_table(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc - 1 < 4 || argc - 1 > 5)
	{
		printf("\033[91;1mERROR: Incorrect number of arguments\033[0m\n");
		printf("\033[1mUsage: ./philo 1)number_of_philo 2)time_to_die \
		3)time_to_eat\n4)time_to_sleep 5)number_of_times_each_philosopher_must_eat\
		(optional argument)\033[0m\n");
		return (1);
	}
	if (!check_input(argc, argv))
		return (1);
	table = init_table(argc, argv);
	if (!table)
		return (1);
	if (!start_simulation(table))
		return (1);
	stop_simulation(table);
	return (0);
}
