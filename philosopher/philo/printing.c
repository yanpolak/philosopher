/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 23:24:40 by ymarival          #+#    #+#             */
/*   Updated: 2023/04/11 15:23:14 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((*(s1 + i) || *(s2 + i)))
	{
		if (*(s1 + i) != *(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
			i++;
	}
	return (0);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_putnbr_ll(long long n)
{
	if (n == LLONG_MIN)
	{
		write(1, "-9223372036854775808", 20);
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		ft_putnbr_ll(-n);
	}
	else if (n > 9)
	{
		ft_putnbr_ll(n / 10);
		ft_putnbr_ll(n % 10);
	}
	else
		ft_putchar(n + '0');
}

void	ft_message(t_data *data, int ph_id, char *str)
{
	int			len;
	uint64_t	tt;

	len = 0;
	while (str[len])
			len++;
	tt = timestamp() - data->table->start_time;
	if (tt >= 0)
	{
		pthread_mutex_lock(&data->table->message);
		ft_putnbr_ll(tt);
		ft_putchar(' ');
		ft_putnbr_ll(ph_id);
		ft_putchar(' ');
		write(1, str, len);
		ft_putchar('\n');
	}
	if (ft_strcmp(str, DIED))
		pthread_mutex_unlock(&data->table->message);
}

int	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error :", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}
