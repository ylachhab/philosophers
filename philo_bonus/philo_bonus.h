/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:25:28 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/25 15:56:13 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>
# include <semaphore.h>

# ifndef SEM_BASE_NAME
#  define SEM_BASE_NAME "last_"
# endif

typedef struct s_arg
{
	int				nbr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	pthread_t		thread;
	sem_t			*eating;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*died;
	long			ftime;
}	t_arg;

typedef struct s_philo
{
	long			last_eat;
	sem_t			*last;
	int				i;
	pid_t			pid;
	int				nbr_of_eat;
	pthread_t		id;
	t_arg			*info;
	struct s_philo	*next;
}	t_philo;

int		ft_atoi(const char *str);
t_philo	*ft_listnew(t_arg *info);
void	ft_listadd_back(t_philo **lst, t_philo *new);
long	ft_time(void);
int		ft_usleep(long time);
void	ft_create_node(t_philo **philo, t_arg *info);
void	ft_free(t_philo *philo, t_arg *info);
int		ft_check_arg(char *s);
int		ft_empty_arg(char *s);
int		ft_parcing(t_arg *info, char **av);
void	ft_sem_printf(t_philo *philo, char *msg);
char	*ft_itoa(int n);
char	*ft_strjoin(char *s1, char *s2);
void	ft_close(t_philo *philo);
void	ft_init_last(t_philo *philo);
void	ft_kill(t_arg *info, t_philo *philo);
void	ft_init(t_arg *info);
void	ft_create_process(t_philo *philo, t_arg *info);
void	*nbr_of_eat(void *arg);
void	ft_create(t_philo *philo, t_arg *info);
void	ft_action(t_philo *philo, t_arg *info);

#endif