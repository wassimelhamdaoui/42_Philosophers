/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 04:14:09 by waelhamd          #+#    #+#             */
/*   Updated: 2022/06/23 04:20:11 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = -1;
	if (!(ac == 5 || ac == 6) || !ft_isnum(av))
	{
		printf("input not valid check agin\n");
		return (0);
	}
	data_init(&data, ac, av);
	while (++i < data.num_philo && data.pid != 0)
	{
		usleep(100);
		data.pid = fork();
		data.id = i + 1;
		data.pids[i] = data.pid;
		if (data.pid == 0)
			pthread_create(&data.check, NULL, (void *)check, &data);
	}
	if (data.pid == 0)
		routine(&data);
	else
		kill_all(&data);
	return (0);
}
