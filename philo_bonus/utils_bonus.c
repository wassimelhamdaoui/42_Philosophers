/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:20:07 by waelhamd          #+#    #+#             */
/*   Updated: 2022/06/23 04:23:10 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sing;
	int	result;

	result = 0;
	sing = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sing++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	if ((sing % 2) != 0)
		return (result * -1);
	return (result);
}

int	ft_isnum(char **av)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (av[j])
	{
		i = 0;
		while (av[j][i])
		{
			if (av[j][i] >= '0' && av[j][i] <= '9')
				i++;
			else
				return (0);
		}
		j++;
	}
	return (1);
}

unsigned long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_time();
	while (get_time() < start + time)
		usleep(50);
}

void	ft_print(t_data *data, char *msg)
{
	sem_wait(data->print);
	printf("%lld %d %s\n", (get_time() - data->start_time), data->id, msg);
	sem_post(data->print);
}
