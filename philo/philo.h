/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:21:16 by ylachhab          #+#    #+#             */
/*   Updated: 2023/04/18 12:12:51 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "../printf/ft_printf.h"

typedef struct s_arg
{
	int	nbr_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	must_eat;
}	t_arg;

typedef struct s_philo
{
	int i;
	pthread_t		id;
	pthread_mutex_t	fork;
	pthread_mutex_t	print;
	t_arg			*info;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

int		ft_atoi(const char *str);
void	ft_error(char *str);

#endif