/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:16:28 by nmoussam          #+#    #+#             */
/*   Updated: 2022/12/06 01:28:42 by nmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*ft_sem_init(char *name, int val)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT, 0777, val);
	if (sem != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	return (sem_open(name, O_CREAT, 0777, val));
}

int	main(int argc, char **argv)
{
	t_infos			info;

	if ((argc != 5 && argc != 6) || ft_check_args(argv) == 0)
		return (printf("Invalid arguments !"), 0);
	if (ft_init_args(argc, argv, &info) == 0)
		return (0);
		
}