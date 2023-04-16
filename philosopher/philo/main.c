/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:40:58 by ymarival          #+#    #+#             */
/*   Updated: 2023/03/30 17:13:16 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_data *data, int i)
{
	while (1)
	{
		i = 0;
		while (i++ < data->table->nbr_ph)
		{
			if (timestamp() - data->ph[i].t_last_meal > data->table->t_die)
			{
				ft_message(data, data->ph->ph_id, DIED);
				return (1);
			}
			i = 0;
			while (i < data->table->nbr_ph && data->ph[i].eat \
			<= data->table->must_to_eat)
			i++;
			if (i < data->table->nbr_ph)
			{
				pthread_mutex_lock(&data->table->message);
				write (1, "THE END\n", 8);
				return (1);
			}
			usleep (500);
		}			
	}
	return (0);
}

void	eating(t_data *data, t_ph *ph)
{
	pthread_mutex_lock(ph->left_fork);
	ft_message(data, ph->ph_id, FORK);
	pthread_mutex_lock(ph->right_fork);
	ft_message(data, ph->ph_id, FORK);
	if (timestamp() - ph->t_last_meal > data->table->t_die)
		pthread_mutex_lock(ph->left_fork);
	ph->t_last_meal = timestamp();
	ft_message(data, ph->ph_id, EAT);
	ft_sleep(data->table->t_eat);
	ph->eat++;
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}

void	*life(void *v_data)
{
	t_data	*data;
	t_ph	*ph;

	data = v_data;
	ph = data->ph + data->ind_cur;
	ph->t_last_meal = timestamp();
	while (1)
	{
		eating(data, ph);
		ft_message(data, ph->ph_id, SLEEP);
		ft_sleep(data->table->t_sleep);
		ft_message(data, ph->ph_id, THINK);
	}
}

int	creating_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->table->nbr_ph)
	{
		data->table->start_time = timestamp();
		data->ind_cur = i;
		if (pthread_create(&data->ph[i].thread_id, NULL, life, data))
			return (-1);
		usleep(50);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_data	data;

	data.table = &table;
	if (argc < 5 || argc > 6)
		return (write_error("Not enough arguments"));
	if (parcing(&table, argv))
		return (write_error("incorrect_arguments"));
	if (init(&data))
		return (write_error("Init"));
	if (creating_philos(&data))
		return (write_error("Create pthreads"));
	monitoring(&data, 0);
	mem_free(&data);
	return (0);
}
