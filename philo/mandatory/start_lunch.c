/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_lunch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:03:41 by nmoussam          #+#    #+#             */
/*   Updated: 2022/12/04 00:28:30 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos(t_philos *philos, t_infos *info)
{
	int	i;
	
	i = 0;
	while (i <  info->nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].nb_meals = 0;
		philos[i].info = info;
		philos[i].died = 0;
		philos[i].start = -1;
		i++;
	}
}

void	print_msg(t_philos *philos, char *msg)
{
	long time;
	time = ft_get_time_now() - philos->start;
	pthread_mutex_lock(&philos->info->msg);
	printf("%ldms philo %d %s\n", time, philos->id, msg);
	pthread_mutex_unlock(&philos->info->msg);
	
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

int check_meals(t_philos *philos)
{
	int i;

	i = 0;
	while (i < philos->info->nb_philos && philos->info->nb_eat > 0)
	{
		if (philos[i].nb_meals <= philos->info->nb_eat)
		{
			philos->died = 1;
			pthread_mutex_lock(&philos->info->msg);
			printf("everyone eat\n");
			pthread_mutex_unlock(&philos->info->msg);
			return (0);
		}
		i++;
	}

	return (1);
}
int check_end(t_philos * philos)
{
	int i;

	i = 0;
	while (i < philos->info->nb_philos)
	{
		if ((philo_died(&philos[i]) == 0 || check_meals(philos) == 0) && philos->start != -1)
			return (0);
		i++;
	}
	return (1);
}


int	ft_begin(t_infos *info, pthread_mutex_t *forks)
{
	t_philos		*philos;
	int 			i;
	
	philos = malloc(sizeof(t_philos) * info->nb_philos);
	if (!philos)
		return (0);
	pthread_mutex_init(&info->msg, NULL);
	ft_init_philos(philos, info);
	i = 0;
	while (i < info->nb_philos)
	{
		get_forks(&philos[i], i, forks, info->nb_philos);
		if (pthread_create(&philos[i].ph, NULL, &routine, &philos[i]) != 0)
			return (0);
		i++;
	}
	if (check_end(philos) == 0)
		return (0);
	return (1);
} 

