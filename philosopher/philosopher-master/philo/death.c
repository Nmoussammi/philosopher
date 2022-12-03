/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:48:23 by ibenmain          #+#    #+#             */
/*   Updated: 2022/12/03 01:59:58 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(pthread_mutex_t *forks, unsigned int nb_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
		pthread_mutex_unlock(&forks[i++]);
}

int	is_dead(t_philo *philo)
{
	if (*philo->finish == 1) \\\\\ mfhmtch ????????
		return (1);
	pthread_mutex_lock(&philo->lunch);
	if ((int)(ft_get_time() - philo->last_meal) >= philo->info->t_die)
	{
		pthread_mutex_unlock(&philo->lunch);
		if (*philo->finish == 0)
		{
			*philo->finish = 1;
			ft_print(philo, "died");
		}
		return (1);
	}
	pthread_mutex_unlock(&philo->lunch);
	return (0);
}

int	check_meals(t_philo *philos, unsigned int nb_philos, long nb_meals)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		if (philos[i].nb_meals < nb_meals)
			return (0);
		i++;
	}
	return (1);
}

int	check_death(t_philo *philos, unsigned int nb_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		if (is_dead(&philos[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_check_philo(t_philo *philos, t_info *info)
{
	while (*philos->finish == 0)
	{
		ft_sleep(3); 
		check_death(philos, info->nb_philo);
		if (*philos->finish == 0 && info->nb_eat > 0
			&& check_meals(philos, info->nb_philo, info->nb_eat))
		{
			*philos->finish = 1;
			ft_sleep(5);
			printf("Everyone ate well\n");
		}
	}
}
