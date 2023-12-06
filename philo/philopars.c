/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philopars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:19:09 by waelhamd          #+#    #+#             */
/*   Updated: 2022/06/22 23:20:22 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

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

t_data	*add_arg(char **av, int ac)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat_num = ft_atoi(av[5]);
	else
		data->must_eat_num = -1;
	data->start_time = get_time();
	if (pthread_mutex_init(&data->print, NULL) == -1)
		return (printf("mutex print was not created"), NULL);
	return (data);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc (sizeof(t_philo) * data->num_philo);
	if (!philo)
		return (NULL);
	while (data->num_philo > ++i)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = get_time();
		if (pthread_mutex_init(&philo[i].fork, NULL) == -1)
			return (printf("mutex fork was not created"), NULL);
		philo[i].args = data;
	}
	return (philo);
}
