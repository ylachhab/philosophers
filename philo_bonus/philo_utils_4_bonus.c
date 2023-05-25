/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_4_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:56:41 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/25 15:57:15 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_create(t_philo *philo, t_arg *info)
{
	ft_init(info);
	ft_init_last(philo);
	ft_create_process(philo, info);
}

void	ft_action(t_philo *philo, t_arg *info)
{
	sem_wait(info->fork);
	ft_sem_printf(philo, "has tacken a fork");
	sem_wait(info->fork);
	ft_sem_printf(philo, "has tacken a fork");
	ft_sem_printf(philo, "is eating");
	sem_wait(philo->last);
	printf("");
	philo->last_eat = ft_time();
	printf("");
	sem_post(philo->last);
	ft_usleep(philo->info->time_eat);
	sem_post(info->fork);
	sem_post(info->fork);
}
