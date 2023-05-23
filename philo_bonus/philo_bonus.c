/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:25:18 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/23 11:25:47 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_printf(t_philo *philo, char *msg)
{
	sem_wait(philo->info->print);
	printf("%ld\t%d\t%s\n", ( ft_time() - philo->info->ftime),
		philo->i, msg);
	sem_post(philo->info->print);
}


void	*ft_is_died(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->last_eat != -1 && ((ft_time() - philo->info->ftime) - philo->last_eat)
			>= philo->info->time_die)
		{
			sem_wait(philo->info->print);
			printf("%ld\t%d\t%s\n", ( ft_time() - philo->info->ftime),
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
	pthread_create(&philo->id, NULL, &ft_is_died, philo);
	while (1)
	{
		sem_wait(info->fork);
		ft_sem_printf(philo, "has tacken a fork");
		sem_wait(info->fork);
		ft_sem_printf(philo, "has tacken a fork");
		ft_sem_printf(philo, "is eating");
		// sem_wait(philo->last);
		philo->last_eat = ft_time() - philo->info->ftime;
		// sem_post(philo->last);
		ft_usleep(philo->info->time_eat);
		sem_post(info->fork);
		sem_post(info->fork);
		ft_sem_printf(philo, "is sleeping");
		ft_usleep(philo->info->time_sleep);
		ft_sem_printf(philo, "is thinking");
		if (philo->info->must_eat > 0)
			philo->nbr_of_eat++;
		if (philo->info->must_eat == philo->nbr_of_eat)
		{
			sem_wait(philo->last);
			philo->last_eat = -1;
			sem_post(philo->last);
			exit (0);
		}
	}
}

void	ft_create_process(t_philo *philo, t_arg *info)
{
	int		i;

	i = 1;
	info->ftime = ft_time();
	while (i <= info->nbr_philo)
	{
		philo->nbr_of_eat = 0;
		philo->pid = fork();
		if (philo->pid == 0)
		{
			// philo->last = sem_open("/philo->last", O_CREAT, 0644, 1);
			// if (philo->last == SEM_FAILED)
			// {
			// 	exit(1);
			// }
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
	int		i;
	int		pid;
	int		status;

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
	sem_unlink("/tmp");
	sem_unlink("/info.fork");
	sem_unlink("/info.died");
	sem_unlink("/info.print");
	// sem_unlink("/philo->last");
	info.t = sem_open("/tmp", O_CREAT, 0644, 1);
	info.fork = sem_open("/info.fork", O_CREAT, 0644, info.nbr_philo);
	info.died = sem_open("/info.died", O_CREAT, 0644, 0);
	info.print = sem_open("/info.print", O_CREAT, 0644, 1);
	philo->nbr_of_eat = 0;
	ft_create_process(philo, &info);
	pid = waitpid(-1, NULL, 0);
	i = 1;
	if (pid != -1)
	{
		usleep(2000);
		while (i <= info.nbr_philo)
		{
			kill(philo->pid, SIGKILL);
			philo = philo->next;
			i++;
		}
		exit (1);
	}
	sem_post(info.t);
	sem_wait(info.died);
	sem_post(info.died);
	i = 1;
	while (i <= info.nbr_philo)
	{
		kill(philo->pid, SIGINT);
		philo = philo->next;
		i++;
	}
	sem_close(info.fork);
	sem_close(info.died);
	sem_close(info.print);
	return (0);
}
