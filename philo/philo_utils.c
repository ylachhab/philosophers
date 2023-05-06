/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:55:50 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/06 10:09:16 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_listnew(t_arg *info)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->info = info;
	new->next = NULL;
	return (new);
}

void	ft_listadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*ptr;

	if (!lst)
		return ;
	ptr = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void	ft_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
			sign = -1;
			i++;
	}
	else if (str[i] == '+')
				i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - 48;
		if ((result > 2147483647 && sign == 1) || result > 2147483648)
			ft_error("error\n");
		i++;
	}
	return (result * sign);
}
