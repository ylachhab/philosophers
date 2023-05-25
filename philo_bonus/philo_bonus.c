/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:25:18 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/25 15:57:11 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_printf(t_philo *philo, char *msg)
{
	sem_wait(philo->info->print);
	printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime),
		philo->i, msg);
	sem_post(philo->info->print);
}

void	*ft_is_died(void *arg)
{
	t_philo	*philo;
	long	las;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->last);
		printf("");
		las = philo->last_eat;
		printf("");
		sem_post(philo->last);
		if (ft_time() >= las + philo->info->time_die)
		{
			sem_wait(philo->info->print);
			printf("%ld\t%d\t%s\n", (ft_time() - philo->info->ftime),
				philo->i, "died");
			sem_post(philo->info->died);
			exit (0);
		}
		usleep(2000);
	}
	return (0);
}

void	ft_routine(t_philo *philo, t_arg *info)
{
	philo->nbr_of_eat = 0;
	philo->last_eat = ft_time();
	if (pthread_create(&philo->id, NULL, &ft_is_died, philo) != 0)
	{
		printf("Error\n");
		exit (1);
	}
	pthread_detach(philo->id);
	while (1)
	{
		ft_action(philo, info);
		ft_sem_printf(philo, "is sleeping");
		ft_usleep(philo->info->time_sleep);
		ft_sem_printf(philo, "is thinking");
		if (philo->info->must_eat > 0)
			philo->nbr_of_eat++;
		if (philo->info->must_eat > 0 && (philo->info->must_eat + 2)
			== philo->nbr_of_eat)
		{
			sem_post(info->eating);
			exit (0);
		}
	}
}

void	ft_create_process(t_philo *philo, t_arg *info)
{
	int	i;

	i = 1;
	info->ftime = ft_time();
	while (i <= info->nbr_philo)
	{
		philo->pid = fork();
		if (philo->pid == 0)
		{
			ft_routine(philo, info);
			usleep(100);
		}
		else if (philo->pid < 0)
		{
			printf("error in fork\n");
			exit (1);
		}
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
	if (info.nbr_philo == 0)
		return (0);
	if (info.nbr_philo < 0 || info.time_die < 0
		|| info.time_eat < 0 || info.time_sleep < 0)
		return (printf("Error\n"), 1);
	info.must_eat = -1;
	if (ac == 6)
		info.must_eat = ft_atoi(av[5]);
	philo = NULL;
	ft_create_node(&philo, &info);
	ft_create(philo, &info);
	if (info.must_eat > 0 && info.nbr_philo > 1)
	{
		if (pthread_create(&info.thread, NULL, nbr_of_eat, &info) != 0)
			return (printf("Error\n"), 1);
		pthread_detach(info.thread);
	}
	return (sem_wait(info.died), ft_kill(&info, philo), 0);
}
