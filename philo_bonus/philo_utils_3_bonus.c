/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:23:06 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/25 15:51:16 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*nbr_of_eat(void *arg)
{
	t_arg	*info;
	int		i;

	info = (t_arg *)arg;
	i = 1;
	while (i++ <= info->nbr_philo)
	{
		sem_wait(info->eating);
		sem_post(info->eating);
	}
	sem_wait(info->print);
	exit (0);
	return (0);
}

void	ft_init(t_arg *info)
{
	sem_unlink("/info->fork");
	sem_unlink("/info->died");
	sem_unlink("/info->print");
	sem_unlink("/info->eating");
	info->fork = sem_open("/info->fork", O_CREAT, 0644, info->nbr_philo);
	info->eating = sem_open("/info->eating", O_CREAT, 0644, 0);
	info->died = sem_open("/info->died", O_CREAT, 0644, 0);
	info->print = sem_open("/info->print", O_CREAT, 0644, 1);
}

void	ft_kill(t_arg *info, t_philo *philo)
{
	int	i;

	i = 1;
	while (i <= info->nbr_philo)
	{
		sem_close(info->fork);
		sem_close(info->died);
		sem_close(info->print);
		sem_close(info->eating);
		sem_close(philo->last);
		kill(philo->pid, SIGKILL);
		philo = philo->next;
		i++;
	}
}

void	ft_close(t_philo *philo)
{
	int	i;

	i = 1;
	while (i <= philo->info->nbr_philo)
	{
		sem_close(philo->last);
		philo = philo->next;
		i++;
	}
}

void	ft_init_last(t_philo *philo)
{
	int		i;
	char	*nbr;
	char	*sem_name;

	i = 1;
	while (i <= philo->info->nbr_philo)
	{
		philo->last_eat = 0;
		nbr = ft_itoa(i);
		sem_name = ft_strjoin(SEM_BASE_NAME, nbr);
		sem_unlink(sem_name);
		philo->last = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
		if (philo->last == SEM_FAILED)
		{
			printf("Error\n");
			exit (1);
		}
		philo = philo->next;
		free(nbr);
		free (sem_name);
		i++;
	}
}
