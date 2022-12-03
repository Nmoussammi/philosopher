/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:09:06 by nmoussam          #+#    #+#             */
/*   Updated: 2022/12/03 21:09:52 by nmoussam         ###   ########.fr       */
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
