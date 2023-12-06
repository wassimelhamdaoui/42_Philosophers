/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:18:19 by waelhamd          #+#    #+#             */
/*   Updated: 2022/06/22 23:30:21 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include<stdlib.h>
# include<stdio.h>
# include<unistd.h>
# include<string.h>
# include<pthread.h>
# include<sys/time.h>

typedef struct s_data
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat_num;
	long long		start_time;
	pthread_mutex_t	print;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				nb_of_meal;
	t_data			*args;
	long long		last_meal;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	pthread_t		thread;
}				t_philo;

int				ft_isnum(char **av);
int				ft_atoi(const char *str);
unsigned long	get_time(void);
void			ft_usleep(unsigned long time);
t_data			*add_arg(char **av, int ac);
t_philo			*init_philo(t_data *data);
void			print_msg(t_philo *philo, char *msg);
void			take_fork(t_philo *philo);
void			leave_fork(t_philo *philo);
void			is_eating(t_philo *philo);
void			*routine(t_philo *philo);
int				death_condition(t_philo *philo);
int				check_death(t_philo *philo);
void			start_philos(t_philo *philo);

#endif