/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:26:31 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/06 10:08:31 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(void)
{
	struct timeval	time;
	long			ret;

	gettimeofday(&time, NULL);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

void	ft_usleep(long time)
{
	long	first_time;

	first_time = ft_time();
	while ((first_time + time) > ft_time())
		usleep(100);
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
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->info->print);
		printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime), philo->i, "has tacken a fork");
		pthread_mutex_unlock(&philo->info->print);

		pthread_mutex_lock(&philo->next->fork);
		pthread_mutex_lock(&philo->info->print);
		printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime), philo->i, "has tacken a fork");
		pthread_mutex_unlock(&philo->info->print);

		pthread_mutex_lock(&philo->info->print);
		printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime), philo->i, "is eating");
		pthread_mutex_lock(&philo->last);
		philo->last_eat = ft_time() - philo->info->ftime;
		pthread_mutex_unlock(&philo->last);
		pthread_mutex_unlock(&philo->info->print);
		ft_usleep(philo->info->time_eat);

		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);

		if (philo->info->must_eat > 0)
			nbr_of_eat++;
		if (philo->info->must_eat == nbr_of_eat)
		{
			philo->last_eat = -1;
			break ;
		}

		pthread_mutex_lock(&philo->info->print);
		printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime), philo->i, "is sleeping");
		pthread_mutex_unlock(&philo->info->print);
		ft_usleep(philo->info->time_sleep);

		pthread_mutex_lock(&philo->info->print);
		printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime), philo->i, "is tinking");
		pthread_mutex_unlock(&philo->info->print);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_arg	info;
	t_philo	*philo;
	t_philo	*new;
	t_philo	*head;
	int		i;
	int		j;

	if (ac == 5 || ac == 6)
	{
		info.nbr_philo = ft_atoi(av[1]);
		info.time_die = ft_atoi(av[2]);
		info.time_eat = ft_atoi(av[3]);
		info.time_sleep = ft_atoi(av[4]);
		if (info.nbr_philo < 0 || info.time_die < 0
			|| info.time_eat < 0 || info.time_sleep < 0)
			ft_error("Error \n");
		if (ac == 6)
			info.must_eat = ft_atoi(av[5]);
		else
			info.must_eat = -1;
		i = 0;
		philo = NULL;
		while (i < info.nbr_philo)
		{
			new = ft_listnew(&info);
			new->i = i;
			new->last_eat = 0;
			ft_listadd_back(&philo, new);
			i++;
		}
		new->next = philo;
		pthread_mutex_init(&info.print, NULL);
		info.ftime = 0;
		i = 0;
		while (i < info.nbr_philo)
		{
			if (!info.ftime)
				info.ftime = ft_time();
			pthread_mutex_init(&philo->fork, NULL);
			pthread_mutex_init(&philo->last, NULL);
			pthread_create(&philo->id, NULL, &ft_routine, philo);
			pthread_detach(philo->id);
			philo = philo->next;
			i++;
		}
		while (1)
		{
			pthread_mutex_lock(&philo->last);
			if (philo->last_eat != -1 && ((ft_time() - info.ftime) - philo->last_eat) >= info.time_die)
			{
				printf("%ld\t%d\t%s\t\n", (ft_time() - philo->info->ftime), philo->i, "died");
				return (1);
			}
			pthread_mutex_unlock(&philo->last);
			j = 0;
			i = 0;
			while (i++ < info.nbr_philo)
			{
				if (philo->last_eat == -1)
					j++;
				philo = philo->next;
			}
			if (j == info.must_eat)
				return (1);
			philo = philo->next;
		}
	}
	else
		printf("Error in the argement\n");
	return (0);
}
