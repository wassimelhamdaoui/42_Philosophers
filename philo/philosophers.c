/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:09:20 by waelhamd          #+#    #+#             */
/*   Updated: 2022/06/22 22:35:14 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_condition(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].args->num_philo)
	{
		if (philo[i].nb_of_meal < philo[0].args->must_eat_num)
			return (1);
		i++;
	}
	return (0);
}

void	free_allocated_memory(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		free(&philo[i]);
		i++;
	}
	free(data);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (get_time() - philo[i].last_meal
			> (unsigned long)philo[0].args->time_die)
		{
			pthread_mutex_lock(&philo->args->print);
			printf("%llu %d die\n", get_time()
				- philo->args->start_time, philo[i].id);
			return (0);
		}
		if (!death_condition(philo) && philo->args->must_eat_num != -1)
			return (0);
		if (i == philo[0].args->num_philo - 1)
			i = 0;
	}
	return (1);
}

void	start_philos(t_philo *philo)
{
	int	i;

	i = -1;
	while (i++ < philo[0].args->num_philo)
	{
		philo[i].next_fork = &philo[(i + 1) % philo[0].args->num_philo].fork;
		philo[i].last_meal = get_time();
		philo[i].nb_of_meal = 0;
	}
	i = -1;
	while (++i < philo[0].args->num_philo)
	{
		pthread_create(&philo[i].thread, NULL, (void *)routine, &philo[i]);
		usleep(50);
	}
	while (1)
	{
		if (!check_death(philo))
			break ;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (!(ac == 5 || ac == 6) || !ft_isnum(av))
	{
		printf("input not valid check again\n");
		return (0);
	}
	data = add_arg(av, ac);
	if (!data)
		return (free(data), 1);
	philo = init_philo(data);
	if (!philo)
		return (free_allocated_memory(philo, data), 1);
	start_philos(philo);
	return (0);
}
