/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sademir <sademir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:18:08 by sademir           #+#    #+#             */
/*   Updated: 2024/03/06 20:31:00 by sademir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

char	*ft_get_status(t_status s)
{
	if (s == EATING)
		return ("is eating");
	else if (s == SLEEPING)
		return ("is sleeping");
	else if (s == THINKING)
		return ("is thinking");
	else if (s == TAKING_FORK)
		return ("has taken a fork");
	else if (s == DIED)
		return ("died");
	return (NULL);
}

bool	ft_safe_print(t_philo *p, t_status status)
{
	bool	rsp;

	rsp = false;
	pthread_mutex_lock(&p->state->print_mutex);
	printf("%llu %d %s\n", ft_now(&p->state), p->id, ft_get_status(status));
	if (p->eaten == p->arg.num_req_eat)
	{
		p->is_finish = true;
		rsp = true;
	}
	pthread_mutex_unlock(&p->state->print_mutex);
	return (rsp);
}
