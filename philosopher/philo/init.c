/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:00:37 by ymarival          #+#    #+#             */
/*   Updated: 2023/04/12 14:34:09 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	men_allocation(t_data *data)
{
	data->ph = malloc(sizeof(*data->ph) * data->table->nbr_ph);
	if (data->ph == NULL)
		return (-1);
	data->table->forks = malloc(sizeof(*data->table->forks) \
						* data->table->nbr_ph);
	if (data->table->forks == NULL)
		return (-1);
	return (0);
}

int	mem_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->table->nbr_ph)
	{
		if (pthread_detach(data->ph[i].thread_id))
			return (-1);
		i++;
	}
	i = 0;
	while (i < data->table->nbr_ph)
	{
		if (pthread_mutex_destroy(data->table->forks + i))
			return (-1);
		i++;
	}
	if (pthread_mutex_destroy(&data->table->message))
		return (-1);
	free(data->ph);
	free(data->table->forks);
	return (0);
}

int	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (table->nbr_ph > i)
	{
		if (pthread_mutex_init(table->forks + i, NULL))
			return (-1);
			i++;
	}
	if (pthread_mutex_init(&table->message, NULL))
		return (-1);
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->table->nbr_ph)
	{
		data->ph[i].ph_id = i + 1;
		data->ph[i].left_fork = &data->table->forks[i];
		data->ph[i].right_fork = &data->table->forks[(i + 1) \
								% data->table->nbr_ph];
		data->ph[i].eat = 0;
		i++;
	}
	return ;
}

int	init(t_data	*data)
{
	if (men_allocation(data))
		return (write_error("mem_allocation"));
	if (init_mutexes(data->table))
		return (write_error("Init mutex"));
	init_philos(data);
	return (0);
}	
