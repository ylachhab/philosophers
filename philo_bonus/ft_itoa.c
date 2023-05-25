/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:26:10 by ylachhab          #+#    #+#             */
/*   Updated: 2023/05/24 10:17:46 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	ptr = malloc (sizeof(char) * i + 1);
	if (!ptr)
		return (NULL);
	while (j < i)
	{
		ptr[j] = s1[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2 || !s1)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i++] = s2[j++];
	}
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}

static size_t	numberof_n(long int n)
{
	long	nb;

	nb = 1;
	while (n >= 10)
	{
		n /= 10;
		nb++;
	}
	return (nb);
}

char	*ft_itoa(int n)
{
	long		a;
	int			len;
	char		*res;
	int			i;

	a = n;
	if (n < 0)
		a *= -1;
	len = numberof_n(a);
	if (n < 0)
		len ++;
	res = malloc(len + 1);
	if (res == 0)
		return (0);
	res[len] = '\0';
	i = len - 1;
	while (i >= 0)
	{
		res[i] = (a % 10) + '0';
		a /= 10;
		i--;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
