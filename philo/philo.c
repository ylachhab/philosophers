/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:26:31 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/06 14:54:52 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->info->print);
	printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime),
		philo->i, "has tacken a fork");
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_lock(&philo->next->fork);
	pthread_mutex_lock(&philo->info->print);
	printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime),
		philo->i, "has tacken a fork");
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_lock(&philo->info->print);
	printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime),
		philo->i, "is eating");
	pthread_mutex_lock(&philo->last);
	philo->last_eat = ft_time() - philo->info->ftime;
	pthread_mutex_unlock(&philo->last);
	pthread_mutex_unlock(&philo->info->print);
	ft_usleep(philo->info->time_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_lock(&philo->info->print);
	printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime),
		philo->i, "is sleeping");
	pthread_mutex_unlock(&philo->info->print);
	ft_usleep(philo->info->time_sleep);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		nbr_of_eat;

	philo = (t_philo *)arg;
	philo->last_eat = 0;
	nbr_of_eat = 0;
	while (1)
	{
		if (philo->i % 2)
			ft_usleep(1);
		ft_action(philo);
		pthread_mutex_lock(&philo->info->print);
		printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime),
			philo->i, "is tinking");
		pthread_mutex_unlock(&philo->info->print);
		if (philo->info->must_eat > 0)
			nbr_of_eat++;
		if (philo->info->must_eat == nbr_of_eat)
		{
			philo->last_eat = -1;
			break ;
		}
	}
	return (0);
}

void	ft_create_thread(t_philo *philo, t_arg *info)
{
	int		i;

	i = 0;
	pthread_mutex_init(&info->print, NULL);
	info->ftime = 0;
	i = 0;
	while (i < info->nbr_philo)
	{
		if (!info->ftime)
			info->ftime = ft_time();
		pthread_mutex_init(&philo->fork, NULL);
		pthread_mutex_init(&philo->last, NULL);
		pthread_create(&philo->id, NULL, &ft_routine, philo);
		philo = philo->next;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_arg	info;
	t_philo	*philo;
	t_philo	*new;

	if (ac == 5 || ac == 6)
	{
		info.nbr_philo = ft_atoi(av[1]);
		info.time_die = ft_atoi(av[2]);
		info.time_eat = ft_atoi(av[3]);
		info.time_sleep = ft_atoi(av[4]);
		if (info.nbr_philo < 0 || info.time_die < 0
			|| info.time_eat < 0 || info.time_sleep < 0)
			ft_error("Error \n");
		info.must_eat = -1;
		if (ac == 6)
			info.must_eat = ft_atoi(av[5]);
		philo = NULL;
		ft_create_node(&philo, &info);
		ft_create_thread(philo, &info);
		if (ft_died(philo, &info))
			return (1);
	}
	else
		printf("Error in the argement\n");
	return (0);
}
