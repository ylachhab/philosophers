/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:21:16 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/06 10:09:42 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_arg
{
	int				nbr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	long			ftime;
	pthread_mutex_t	print;
}	t_arg;

typedef struct s_philo
{
	int				i;
	long			last_eat;
	pthread_t		id;
	pthread_mutex_t	fork;
	pthread_mutex_t	last;
	t_arg			*info;
	struct s_philo	*next;
}	t_philo;

int		ft_atoi(const char *str);
void	ft_error(char *str);
t_philo	*ft_listnew(t_arg *info);
void	ft_listadd_back(t_philo **lst, t_philo *new);
long	ft_time(void);
void	ft_usleep(long time);

#endif