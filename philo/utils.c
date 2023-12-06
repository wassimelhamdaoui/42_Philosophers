/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:24:41 by waelhamd          #+#    #+#             */
/*   Updated: 2022/06/22 23:24:47 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->args->print);
	printf("%lld %d %s\n", (get_time() - philo->args->start_time),
		philo->id, msg);
	pthread_mutex_unlock(&philo->args->print);
}
