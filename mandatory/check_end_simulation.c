/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:59:24 by nmoussam          #+#    #+#             */
/*   Updated: 2022/12/05 16:09:09 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philos *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philos->info->nb_philos)
	{
		if (pthread_mutex_destroy(&forks[i]) != 0)
			break ;
		i++;
	}
	pthread_mutex_destroy(&philos->info->msg);
	free(philos);
}

int	check_philos(t_infos *infos, t_philos *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	(void)infos;
	while (1)
	{
		if (ft_get_time_now() - philos[i].last_meal > philos[i].info->time_die)
		{
			pthread_mutex_lock(&philos->info->msg);
			print_msg(philos, "died ⚰️");
			return (ft_free(philos, forks), usleep(500), 0);
		}
		if (philos[i].nb_meals == philos->info->nb_eat)
		{
			philos->died = 1;
			pthread_mutex_lock(&philos->info->msg);
			printf("everyone eat\n");
			return (ft_free(philos, forks), usleep(500), 0);
		}
		i = (i + 1) % philos->info->nb_philos;
	}
	free(philos);
	return (1);
}
