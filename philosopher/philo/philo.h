/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:26:06 by ymarival          #+#    #+#             */
/*   Updated: 2023/04/16 22:04:40 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

# define DIED "died"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is slepping"
# define THINK "is thinking"

typedef struct s_ph
{
	int						ph_id;
	int						eat;
	uint64_t				t_last_meal;
	pthread_t				thread_id;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
}		t_ph;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	uint64_t		start_time;
	int				nbr_ph;
	uint64_t		t_die;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	int				must_to_eat;
	int				all_eat;
}		t_table;

typedef struct s_data
{
	t_ph	*ph;
	t_table	*table;
	int		ind_cur;
}	t_data;

int			parcing(t_table *table, char **argv);
int			mem_allocation(t_data *data);
int			mem_free(t_data *data);
void		init_philos(t_data *data);
int			init(t_data *data);
int			init_mutexes(t_table *table);
int			write_error(char *str);
void		ft_message(t_data *data, int ph_id, char *str);
uint64_t	timestamp(void);
void		ft_sleep(uint64_t time);
int			monitoring(t_data *data, int i);
void		eating(t_data *data, t_ph *ph);
#endif
