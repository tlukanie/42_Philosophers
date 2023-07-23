/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:34:42 by tlukanie          #+#    #+#             */
/*   Updated: 2023/07/23 15:42:50 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_table(t_table *table)
{
	unsigned int	i;

	if (!table)
		return (NULL);
	if (table->fork_mutexes != NULL)
		free(table->fork_mutexes);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->philos_amount)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
	return (NULL);
}

void	destroy_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->philos_amount)
	{
		pthread_mutex_destroy(&table->fork_mutexes[i]);
		pthread_mutex_destroy(&table->philos[i]->meal_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->output_mutex);
	pthread_mutex_destroy(&table->stop_status_mutex);
}

static bool	digits_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	custom_atoi(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > 2147483647)
		return (-1);
	return ((int)nb);
}

bool	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!digits_only(argv[i]))
		{
			printf("\033[91;1mERROR: Invalid input\033[0m\n");
			return (false);
		}
		if (i == 1 && (custom_atoi(argv[i]) <= 0
				|| custom_atoi(argv[i]) > MAX_PHILOS))
		{
			printf("\033[91;1mERROR: Invalid input\033[0m\n");
			printf("\033[1mEnter between 1 and 250 philosophers\033[0m\n");
			return (false);
		}
		if (i != 1 && custom_atoi(argv[i]) == -1)
		{
			printf("\033[91;1mERROR: Invalid input\033[0m\n");
			return (false);
		}
		i++;
	}
	return (true);
}
