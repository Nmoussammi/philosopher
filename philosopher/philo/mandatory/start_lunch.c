/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_lunch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:03:41 by nmoussam          #+#    #+#             */
/*   Updated: 2022/12/03 15:54:17 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_philos *philos, int id, pthread_mutex_t *fork, int nb_philo)
{
	if (id == 0)
	{
		philos->left_fork = &fork[nb_philo - 1];
		philos->right_fork = &fork[0];
	}
	else
	{
		philos->left_fork = &fork[id - 1];
		philos->right_fork = &fork[id];
	}
}

void	ft_init_philos(t_philos *philos, t_infos *info, pthread_mutex_t *msg)
{
	int	i;
	
	i = 0;
	while (i <  info->nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].nb_meals = 0;
		philos[i].info = info;
		philos[i].msg = msg;
		philos[i].last_meal = ft_get_time_now();
		philos[i].died = 0;
		i++;
	}
}
long	ft_get_time_now()
{
	struct  timeval	tp;
	long			ms;
	
	gettimeofday(&tp, NULL);
	ms = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	return (ms);
}

void	ft_usleep(int time, t_philos *philos)
{
	philos->start = ft_get_time_now();
	while (((ft_get_time_now() - philos->start) <= time) && philos->died == 0)
		usleep(100);
}


void	print_msg(t_philos *philos, char *msg)
{
	long time;
	time = ft_get_time_now() - philos->start;
	pthread_mutex_lock(philos->msg);
	printf("%ldms philo %d %s\n", time, philos->id, msg);
	pthread_mutex_unlock(philos->msg);
	
}
int pickup_forks(t_philos *philos)
{
	if (philos->died == 1)
		return (0);
	pthread_mutex_lock(philos->left_fork);
	if (philos->died == 1)
		return (0);
	print_msg(philos, "has taken a fork 🍴");
	pthread_mutex_lock(philos->right_fork);
	if (philos->died == 1)
		return (0);
	print_msg(philos, "has taken a fork 🍴");
	return (1);	
}

int eating(t_philos *philos)
{
	print_msg(philos, "is eating 🍝");
	philos->last_meal = ft_get_time_now();
	philos->nb_meals++;
	ft_usleep(philos->info->time_eat, philos);
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
	if (philos->died == 1)
		return (0);
	return (1);
}

int	sleeping_thinking(t_philos *philos)
{
	if (philos->died == 1)
		return (0);
	print_msg(philos, "is sleeping 😴");
	ft_usleep(philos->info->time_sleep, philos);
	if (philos->died == 1)
		return (0);
	print_msg(philos, "is thinking 🤔");
	return (1);
}

void	*routine(void *args)
{
	t_philos		*philos;

	philos = (t_philos *)args;
	if (philos->id % 2 == 0)
		ft_usleep(100, philos);	
	while(philos->died == 0)
	{
		if (pickup_forks(philos) == 0)
			return (0);
		if (eating(philos) == 0)
			return (0);
		if (sleeping_thinking(philos) == 0)
			return (0);
	}
	return (NULL);
}
int philo_died(t_philos *philos)
{
	if ((ft_get_time_now() - philos->last_meal) >= philos->info->time_die)
	{
		philos->died = 1;
		print_msg(philos, "died ⚰️");
		return (0);
	}
	return (1);
}

int check_end(t_philos *philos, t_infos *infos)
{
	int i;

	i = 0;
	while (i < infos->nb_philos)
	{
		if (philo_died(&philos[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
int check_meals(t_philos *philos, t_infos *infos)
{
	int i;

	i = 0;
	while (i < infos->nb_philos)
	{
		if (philos[i].nb_meals <= infos->nb_eat)
		{
			philos->died = 1;
			return (0);
		}
		i++;
	}
	print_msg(philos, "everyone eat");
	return (1);
}

int check_philos(t_infos *infos, t_philos *philos)
{
	int i;

	i = 0;
	while (philos->died == 0)
	{
		if (check_end(philos, infos) == 0 || check_meals(philos, infos))
			return (0);
	}
	while (i < infos->nb_philos)
	{
		if (pthread_join(philos[i].ph, NULL) != 0)
			return (0);
		i++;
	}
	free(philos);
	return (1);
}

int	ft_begin(t_infos *info, pthread_mutex_t *forks)
{
	t_philos		*philos;
	pthread_mutex_t	msg;
	int 			i;
	
	philos = malloc(sizeof(t_philos) * info->nb_philos);
	if (!philos)
		return (0);
	pthread_mutex_init(&msg, NULL);
	ft_init_philos(philos, info, &msg);
	i = 0;
	while (i < info->nb_philos)
	{
		get_forks(&philos[i], i, forks, info->nb_philos);
		if (pthread_create(&philos[i].ph, NULL, &routine, &philos[i]) != 0)
			return (0);
		i++;
	}
	if (check_philos(info, philos) == 0)
		return (0);
	return (1);
}