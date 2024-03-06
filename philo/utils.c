/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sademir <sademir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:24:02 by sademir           #+#    #+#             */
/*   Updated: 2024/03/06 20:42:28 by sademir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

int64_t	ft_atol(const char *str)
{
	size_t		i;
	int			sign;
	int64_t		num;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (sign * num);
}

bool	ft_str_alldigit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

u_int64_t	ft_now(t_state **s)
{
	u_int64_t	time;

	gettimeofday(&(*s)->tv, NULL);
	time = ((*s)->tv.tv_sec * 1000)
		+ ((*s)->tv.tv_usec / 1000 - (*s)->start_time);
	return (time);
}

void	ft_usleep(t_state **s, u_int64_t time)
{
	u_int64_t	dest;

	dest = ft_now(s) + time;
	while (ft_now(s) < dest)
		usleep(100);
}
