/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:26:31 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/14 13:09:59 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mutex_printf(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->print);
	printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime),
		philo->i, msg);
	pthread_mutex_unlock(philo->print);
}

int	ft_action(t_philo *philo)
{
	long	current;

	pthread_mutex_lock(&philo->fork);
	ft_mutex_printf(philo, "has tacken a fork");
	pthread_mutex_lock(&philo->next->fork);
	ft_mutex_printf(philo, "has tacken a fork");
	ft_mutex_printf(philo, "is eating");
	pthread_mutex_lock(&philo->last);
	philo->last_eat = ft_time() - philo->info->ftime;
	pthread_mutex_unlock(&philo->last);
	current = ft_time();
	if (ft_usleep(philo->info->time_eat, current, philo))
	{
		return (1);
	}
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	ft_mutex_printf(philo, "is sleeping");
	current = ft_time();
	if (ft_usleep(philo->info->time_sleep, current, philo))
		return (1);
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		nbr_of_eat;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->last);
	philo->last_eat = 0;
	pthread_mutex_unlock(&philo->last);
	nbr_of_eat = 0;
	while (1)
	{
		if (philo->i % 2)
			usleep(500);
		if (ft_action(philo))
			break ;
		ft_mutex_printf(philo, "is thinking");
		if (philo->info->must_eat > 0)
			nbr_of_eat++;
		if (philo->info->must_eat == nbr_of_eat)
		{
			ft_mutex_last(philo);
			break ;
		}
	}
	return (0);
}

void	ft_create_thread(t_philo *philo, t_arg *info)
{
	int		i;

	i = 0;
	info->ftime = 0;
	while (i < info->nbr_philo)
	{
		if (!info->ftime)
			info->ftime = ft_time();
		if (pthread_create(&philo->id, NULL, &ft_routine, philo) != 0)
			return ;
		pthread_detach(philo->id);
		philo = philo->next;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_arg	info;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (printf("Error in the argement\n"), 0);
	if (ft_parcing(&info, av))
		return (printf("Error in the argement\n"), 1);
	if (info.nbr_philo < 0 || info.time_die < 0
		|| info.time_eat < 0 || info.time_sleep < 0)
		return (printf("%s\n", "Error"), 1);
	info.must_eat = -1;
	if (ac == 6)
		info.must_eat = ft_atoi(av[5]);
	philo = NULL;
	info.print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(info.print, NULL);
	ft_create_node(&philo, &info);
	ft_create_thread(philo, &info);
	if (philo && ft_died(philo, &info))
		return (0);
	return (0);
}
