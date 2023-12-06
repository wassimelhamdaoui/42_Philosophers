/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:58:51 by waelhamd          #+#    #+#             */
/*   Updated: 2022/06/22 23:25:02 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->next_fork);
		print_msg(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->next_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork);
		print_msg(philo, "has taken a fork");
	}
}

void	leave_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->next_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->next_fork);
		pthread_mutex_unlock(&philo->fork);
	}
}

void	is_eating(t_philo *philo)
{
	print_msg(philo, "is eating");
	ft_usleep(philo->args->time_eat);
	philo->last_meal = get_time();
	philo->nb_of_meal++;
}

void	*routine(t_philo *philo)
{
	while (1)
	{
		take_fork(philo);
		is_eating(philo);
		leave_fork(philo);
		print_msg(philo, "is sleeping");
		ft_usleep(philo->args->time_sleep);
		print_msg(philo, "is thinking");
	}
}
