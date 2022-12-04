/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:01:18 by nmoussam          #+#    #+#             */
/*   Updated: 2022/12/05 00:22:03 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos(t_philos *philos, t_infos *info)
{
	int	i;
	long start;

	i = 0;
	start = ft_get_time_now();
	while (i < info->nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].nb_meals = 0;
		philos[i].info = info;
		philos[i].died = 0;
		philos[i].start = start;
		i++;
	}
}

int	ft_begin(t_infos *info, pthread_mutex_t *forks)
{
	t_philos	*philos;
	int			i;

	philos = malloc(sizeof(t_philos) * info->nb_philos);
	if (!philos)
		return (0);
	pthread_mutex_init(&info->msg, NULL);
	ft_init_philos(philos, info);
	i = 0;
	while (i < info->nb_philos)
	{
		get_forks(&philos[i], i, forks, info->nb_philos);
		// philos[i].start = ft_get_time_now();
		if (pthread_create(&philos[i].ph, NULL, &routine, &philos[i]) != 0)
			return (0);
		usleep(100);
		// usleep mabin lreation dyal kola tread w bach maysb9ch 2 3la 1 w yakhod lfork dyalo
		i++;
	}
	i = 0;
	while (i < info->nb_philos)
	{
		if (pthread_detach(philos[i].ph) != 0)
			return (0);
		i++;
	}
	if (check_philos(info, philos) == 0)
		return (0);
	// usleep(200 * 1000);
	return (1);
}
