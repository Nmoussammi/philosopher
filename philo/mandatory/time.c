/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:30:29 by nmoussam          #+#    #+#             */
/*   Updated: 2022/12/03 19:12:22 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	long start = ft_get_time_now();
	while (((ft_get_time_now() - start) <= time) && philos->died == 0)
		usleep(100);
}
