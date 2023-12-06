/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:22:42 by waelhamd          #+#    #+#             */
/*   Updated: 2022/06/22 23:40:04 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include<stdlib.h>
# include<stdio.h>
# include<unistd.h>
# include<string.h>
# include<pthread.h>
# include<sys/time.h>
# include<fcntl.h>
# include<signal.h>
# include<sys/stat.h>
# include<semaphore.h>

typedef struct s_data
{
	int			id;
	int			num_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			must_eat_num;
	int			num_of_meals;
	long long	last_meal;
	long long	start_time;
	pid_t		pid;
	pid_t		*pids;
	sem_t		*fork;
	sem_t		*print;
	pthread_t	check;
}				t_data;

int				ft_atoi(const char *str);
int				ft_isnum(char **av);
unsigned long	get_time(void);
void			ft_usleep(unsigned long time);
void			data_init(t_data *data, int ac, char **av);
void			ft_print(t_data *data, char *msg);
void			routine(t_data *data);
void			*check(t_data *data);
void			ft_kill(t_data *data);
void			kill_all(t_data *data);

#endif