/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:58:36 by nmoussam          #+#    #+#             */
/*   Updated: 2022/12/05 00:14:52 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int pickup_forks(t_philos *philos)
{
	if (philos->died == 1)
		return (0);
    // if (philos->info->nb_philos == 1)
    // {
    //     pthread_mutex_lock(philos->left_fork);
	//     print_msg(philos, "has taken a fork 🍴");
    //     ft_usleep(philos->info->time_die, philos);
    //     pthread_mutex_lock(&philos->info->msg);
    //     print_msg(philos, "died");
    //     return(0);
    // }
	pthread_mutex_lock(philos->left_fork);
	if (philos->died == 1)
		return (0);
    pthread_mutex_lock(&philos->info->msg);
	print_msg(philos, "has taken a fork 🍴");
    pthread_mutex_unlock(&philos->info->msg);
	pthread_mutex_lock(philos->right_fork);
	if (philos->died == 1)
		return (0);
    pthread_mutex_lock(&philos->info->msg);
	print_msg(philos, "has taken a fork 🍴");
    pthread_mutex_unlock(&philos->info->msg);
	return (1);	
}

int eating(t_philos *philos)
{
    pthread_mutex_lock(&philos->info->msg);
	print_msg(philos, "is eating 🍝");
    pthread_mutex_unlock(&philos->info->msg);
    ;//
	philos->last_meal = ft_get_time_now();
    ;//
    ;//
	philos->nb_meals++;//mutex
    ;//
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
    pthread_mutex_lock(&philos->info->msg);
	print_msg(philos, "is sleeping 😴");
    pthread_mutex_unlock(&philos->info->msg);
	ft_usleep(philos->info->time_sleep, philos);
	if (philos->died == 1)
		return (0);
    pthread_mutex_lock(&philos->info->msg);
	print_msg(philos, "is thinking 🤔");
    pthread_mutex_unlock(&philos->info->msg);
	return (1);
}

void	*routine(void *args)
{
	t_philos		*philos;

	philos = (t_philos *)args;
    // philos->start = ft_get_time_now();
    // philos->last_meal = philos->start;
    philos->last_meal = ft_get_time_now();
	if (philos->id % 2 == 0)
		ft_usleep(100, philos);	
    // while true and the dead main thread will check for it
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