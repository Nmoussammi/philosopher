/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:23:24 by nmoussam          #+#    #+#             */
/*   Updated: 2022/12/03 01:49:00 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	resultat;
	int			sign;

	i = 0;
	sign = 1;
	resultat = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + (int)(str[i] - '0');
		i++;
	}
	return (sign * resultat);
}

int    ft_init_args(int argc, char **argv, t_infos *info)
{
	info->nb_philos = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		info->nb_eat = ft_atoi(argv[5]);
		if (info->nb_eat <= 0)
			return (printf("Invalid Arguments !!"), 0);
	}
	if (info->nb_philos <= 0 || info->time_eat <= 0 || info->time_sleep <= 0
		|| info->time_die <= 0)
		return (printf("Invalid Arguments !!"), 0);
	return (1);
}