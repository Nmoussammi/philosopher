/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:08:24 by nmoussam          #+#    #+#             */
/*   Updated: 2022/12/03 21:26:14 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

pthread_mutex_t	*ft_init_mutex(t_infos *info) // init mutex
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * info->nb_philos);
	if (!forks)
		return (0);
	while (i < info->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (0); 
		i++;
	}
	return (forks);
}
