/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:34:42 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/23 10:49:58 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_create_node(t_philo **philo, t_arg *info)
{
	int		i;
	t_philo	*new;

	i = 1;
	new = NULL;
	while (i <= info->nbr_philo)
	{
		new = ft_listnew(info);
		new->i = i;
		new->last_eat = 0;
		ft_listadd_back(philo, new);
		i++;
	}
	new->next = *philo;
}

long	ft_time(void)
{
	struct timeval	time;
	long			ret;

	gettimeofday(&time, NULL);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

int	ft_usleep(long time)
{
	long	first_time;

	first_time = ft_time();
	while (ft_time() - first_time < time)
		usleep(100);
	return (0);
}
