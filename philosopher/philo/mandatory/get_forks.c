/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:42:19 by nmoussam          #+#    #+#             */
/*   Updated: 2022/12/03 15:27:16 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*ft_init_forks(t_infos *info) // init mutex
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