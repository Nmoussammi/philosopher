/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:59:24 by nmoussam          #+#    #+#             */
/*   Updated: 2022/12/04 23:50:57 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	philo_died(t_philos *philos)
// {
// 	if ((ft_get_time_now() - philos->last_meal) >= philos->info->time_die)
// 	{
// 		philos->died = 1;
// 		pthread_mutex_lock(&philos->info->msg);
// 		print_msg(philos, "died ⚰️");
// 		return (0);
// 	}
// 	return (1);
// }

// int check_end(t_philos *philos, t_infos *infos)
// {
// 	int i;

// 	i = 0;
// 	while (i < infos->nb_philos)
// 	{
// 		if (philo_died(&philos[i]) == 0)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int check_meals(t_philos *philos)
// {
// 	int i;

// 	i = 0;
// 	while (i < philos->info->nb_philos && philos->info->nb_eat > 0)
// 	{
// 		if (philos[i].nb_meals == philos->info->nb_eat)
// 		{
// 			philos->died = 1;
// 			pthread_mutex_lock(&philos->info->msg);
// 			printf("everyone eat\n");
// 			return (0);
// 		}
// 		i++;
// 	}

// 	return (1);
// }

int check_philos(t_infos *infos, t_philos *philos)
{
	int i;
	int x;

	i = 0;
	x = 1;
	// philos->start = ft_get_time_now();
	// while (philos->died == 0)
	// {
	// 	if ((check_end(philos, infos) == 0 || check_meals(philos) == 0))
	// 		return (0);
	// }
	(void)infos;
	while (1)
	{
		if (ft_get_time_now() - philos[i].last_meal > philos[i].info->time_die)
		{
			pthread_mutex_lock(&philos->info->msg);
			print_msg(philos, "died ⚰️");
			return (free(philos), usleep(500), 0);
		}
		if (philos[i].nb_meals == philos->info->nb_eat)
		{
			philos->died = 1;
			pthread_mutex_lock(&philos->info->msg);
			printf("everyone eat\n");
			return (free(philos), usleep(500), 0);
		}
		i = (i + 1) % philos->info->nb_philos;// 0 1 2 3  4 5 0 1 2 3 4 5 0 1 2 3 4 5// 5
		/*
		i++;
		if (i == nbr_philos)
			i=0;
		*/
	}
	free(philos);
	return (1);
}