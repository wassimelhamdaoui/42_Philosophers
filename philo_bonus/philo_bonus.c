/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:34:17 by waelhamd          #+#    #+#             */
/*   Updated: 2022/06/23 04:20:27 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	data_init(t_data *data, int ac, char **av)
{
	data->id = 0;
	data->num_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat_num = ft_atoi(av[5]);
	data->num_of_meals = 0;
	data->last_meal = get_time();
	data->start_time = get_time();
	data->pid = 1;
	data->pids = malloc(sizeof(pid_t) * data->num_philo);
	sem_unlink("fork");
	data->fork = sem_open("fork", O_CREAT, S_IRWXU, data->num_philo);
	sem_unlink("print");
	data->print = sem_open("print", O_CREAT, S_IRWXU, 1);
}

void	routine(t_data *data)
{
	while (1)
	{
		sem_wait(data->fork);
		ft_print(data, "has taken a fork");
		sem_wait(data->fork);
		ft_print(data, "has taken a fork");
		ft_print(data, "is eating");
		ft_usleep(data->time_eat);
		data->last_meal = get_time();
		data->num_of_meals++;
		sem_post(data->fork);
		sem_post(data->fork);
		if (data->must_eat_num && data->must_eat_num <= data->num_of_meals)
			exit(0);
		ft_print(data, "is sleeping");
		ft_usleep(data->time_sleep);
		ft_print(data, "is thinking");
	}
}

void	*check(t_data *data)
{
	while (1)
	{
		usleep(500);
		if ((get_time() - data->last_meal) >= (unsigned long)(data->time_die))
		{
			sem_wait(data->print);
			printf("%llu %d died\n", get_time() - data->start_time, data->id);
			exit(0);
		}
	}
}

void	ft_kill(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	free(data->pids);
}

void	kill_all(t_data *data)
{
	int	i;

	i = 1;
	while (1)
	{
		waitpid(-1, &i, 0);
		if (i == 0)
		{
			ft_kill(data);
			break ;
		}
	}
}
