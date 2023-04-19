/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:26:31 by ylachhab          #+#    #+#             */
/*   Updated: 2023/04/18 21:48:01 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

t_philo	*ft_listnew(t_arg *info)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->info = info;
	new->prev = new;
	new->next = new;
	return (new);
}

void	ft_listadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;
	t_philo	*begin;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		begin = *lst;
		last = begin->prev;
		last->next = new;
		new->prev = last;
		new->next = begin;
		begin->prev = new;
	}
}

void	*routine(void	*arg)
{
	t_philo *philo = (t_philo *)arg;
	int i = 0;
	while (i < 2)
	{
		if (philo->i % 2)
			usleep(50);
		pthread_mutex_lock(&philo->fork);

		pthread_mutex_lock(&philo->print);
		printf("[%d]%s\n", philo->i, "has taken a fork");
		pthread_mutex_unlock(&philo->print);

		pthread_mutex_lock(&philo->next->fork);

		pthread_mutex_lock(&philo->print);
		printf("[%d]%s\n", philo->i,"has taken a fork");
		pthread_mutex_unlock(&philo->print);

		pthread_mutex_lock(&philo->print);
		printf("[%d]%s\n", philo->i,"is eating");
		pthread_mutex_unlock(&philo->print);
		usleep(50);

		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);

		pthread_mutex_lock(&philo->print);
		printf("[%d]%s\n", philo->i,"is sleeping");
		pthread_mutex_unlock(&philo->print);
		usleep(50);
		i++;
	}
	return (0);
}

int ft_time()
{
	struct timeval time;
	int	ret;

	gettimeofday(&time, NULL);
	ret = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ret);
}

int	ft_usleep(int time)
{
	int	first_time;

	first_time = ft_time();
	while ((first_time + time) > ft_time())
		usleep (50);
}

int	main(int ac, char **av)
{
	t_arg	info;
	t_philo	*philo;
	t_philo	*new;
	t_philo	*head;
	int		i;

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
			info.must_eat = 0;
		i = 0;
		while (i < info.nbr_philo)
		{
			new = ft_listnew(&info);
			ft_listadd_back(&philo, new);
			new->i = i;
			i++;
		}
		while (philo)
		{
			pthread_mutex_init(&philo->fork, NULL);
			pthread_mutex_init(&philo->print, NULL);
			pthread_create(&philo->id, NULL, &routine, philo);
			pthread_detach(philo->id);
			philo = philo->next;
		}
		philo = philo->next;
		while (philo)
		{
			pthread_join(philo->id, NULL);
			philo = philo->next;
		}
		// t_philo *begin;
		// begin = philo;
		// while (philo->next != begin)
		// {
		// 	printf("| %d |\n", philo->i);
		// 	philo = philo->next;
		// }
		// 	printf("| %d |\n", philo->i);
		// 	philo = philo->next;
		// 	printf("| %d |\n", philo->i);
	}
	else
		printf("Error in the argement\n");
}
