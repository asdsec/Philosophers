/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sademir <sademir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:17:22 by sademir           #+#    #+#             */
/*   Updated: 2024/03/06 20:34:12 by sademir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_is_finish_first_loop(t_philo *p)
{
	bool	rsp;

	rsp = false;
	pthread_mutex_lock(&p->state->first_philos_mutex);
	if (p->state->first_philo_count == 0)
		rsp = true;
	pthread_mutex_unlock(&p->state->first_philos_mutex);
	return (rsp);
}

void	ft_decrease_first_philos(t_philo *p)
{
	pthread_mutex_lock(&p->state->first_philos_mutex);
	if (p->state->first_philo_count > 0)
		p->state->first_philo_count--;
	pthread_mutex_unlock(&p->state->first_philos_mutex);
}
