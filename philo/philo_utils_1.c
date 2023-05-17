/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:34:42 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/17 19:58:01 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_last_eat(t_philo *philo, t_arg *info)
{
	int		i;
	int		j;
	t_philo	*head;

	j = 0;
	i = 0;
	while (i < info->nbr_philo)
	{
		pthread_mutex_lock(&philo->last);
		if (philo->last_eat == -1)
			j++;
		pthread_mutex_unlock(&philo->last);
		philo = philo->next;
		i++;
	}
	if (j == info->nbr_philo)
	{
		ft_free(philo, info);
		return (1);
	}
	return (0);
}

int	ft_died(t_philo *philo, t_arg *info)
{
	while (1)
	{
		pthread_mutex_lock(&philo->last);
		if ((philo->last_eat != -1)
				&& (ft_time() - info->ftime) - philo->last_eat
				>= info->time_die)
		{
			pthread_mutex_lock(philo->print);
			printf("%ld\t%d\t%s\t\n", (ft_time() - philo->info->ftime),
				philo->i, "died");
			return (1);
		}
		pthread_mutex_unlock(&philo->last);
		if (ft_last_eat(philo, info))
			return (1);
		philo = philo->next;
	}
	return (0);
}

void	ft_create_node(t_philo **philo, t_arg *info)
{
	int		i;
	t_philo	*new;

	i = 0;
	new = NULL;
	while (i < info->nbr_philo)
	{
		new = ft_listnew(info);
		new->i = i;
		new->last_eat = 0;
		new->print = info->print;
		pthread_mutex_init(&new->fork, NULL);
		pthread_mutex_init(&new->last, NULL);
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

int	ft_usleep(long time, long current, t_philo *philo)
{
	long	first_time;

	first_time = ft_time();
	while (ft_time() - current < time)
	{
		if (((ft_time() - philo->info->ftime) - philo->last_eat)
			>= philo->info->time_die)
			return (1);
		usleep(100);
	}
	return (0);
}
