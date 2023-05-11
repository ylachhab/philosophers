/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:43:31 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/10 19:15:18 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parcing(t_arg *info, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_check_arg(av[i]))
			return (1);
		i++;
	}
	info->nbr_philo = ft_atoi(av[1]);
	info->time_die = ft_atoi(av[2]);
	info->time_eat = ft_atoi(av[3]);
	info->time_sleep = ft_atoi(av[4]);
	return (0);
}

int	ft_check_arg(char *s)
{
	int	i;
	int	ss;

	ss = 0;
	if (!ft_empty_arg(s))
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '+')
		{
			if ((s[i - 1] >= '0' && s[i - 1] <= '9')
				|| !(s[i + 1] >= '0' && s[i + 1] <= '9'))
				return (0);
		}
		else if ((s[i] != '+' && s[i] != ' ' && s[i] != '\t'
				&& !(s[i] >= '0' && s[i] <= '9')) || (i && ss))
			return (0);
		if (s[i] == ' ')
			ss++;
		i++;
	}
	return (1);
}

int	ft_empty_arg(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (s[i] == '\0')
		return (0);
	return (1);
}

void	ft_mutex_usleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->died_m);
	philo->info->died = philo->i;
	pthread_mutex_unlock(&philo->info->died_m);
}

void	ft_free(t_philo *philo, t_arg *info)
{
	int		i;
	t_philo	*head;

	i = 0;
	while (i++ < info->nbr_philo)
	{
		pthread_mutex_destroy(&philo->fork);
		pthread_mutex_destroy(&philo->last);
		head = philo;
		philo = philo->next;
		free(head);
	}
	pthread_mutex_destroy(info->print);
	free(info->print);
	pthread_mutex_destroy(&info->died_m);
}
