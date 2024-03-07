/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sademir <sademir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:14:02 by sademir           #+#    #+#             */
/*   Updated: 2024/03/07 17:39:48 by sademir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <stdlib.h>

static int	ft_check_arg(int ac, char **av);
static void	ft_start(t_state **s);
static void	*ft_routine(void *arg);
static int	ft_monitor(t_philo *p);

int	main(int ac, char **av)
{
	t_state	*s;
	int		rsp;

	if (!(ac == 5 || ac == 6))
		return (ft_errmsg(1, "invalid argument count", NULL));
	rsp = ft_check_arg(ac, av);
	if (rsp != R_SUCCESS)
		return (rsp);
	rsp = ft_init_state(&s, ac, av);
	if (rsp != R_SUCCESS)
		return (rsp);
	ft_start(&s);
}

static int	ft_check_arg(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_str_alldigit(av[i]))
			return (ft_errmsg(2, "all characters are not digits!", NULL));
		if (av[i][0] == '0')
			return (ft_errmsg(3, "zero is not allowed!", NULL));
		i++;
	}
	return (R_SUCCESS);
}

static void	ft_start(t_state **s)
{
	int	i;

	i = 0;
	(*s)->start_time = ft_now(s);
	while (i < (*s)->arg.num_philo)
	{
		pthread_create(&(*s)->philos[i].th, NULL, ft_routine, &(*s)->philos[i]);
		i++;
	}
	while (true)
	{
		i = 0;
		while (i < (*s)->arg.num_philo)
		{
			if (ft_monitor(&(*s)->philos[i]) != R_SUCCESS)
			{
				ft_dispose_state(s);
				return ;
			}
			i++;
		}
	}
}

static void	*ft_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *) arg;
	ft_think_for_one_on_odd(p);
	while (true)
	{
		if (p->is_first_loop)
		{
			if (p->id % 2 == 1)
			{
				if (ft_eat(p))
					return (NULL);
			}
			else
			{
				if (ft_think(p))
					return (NULL);
			}
			p->is_first_loop = false;
		}
		if (ft_is_finish_first_loop(p))
			if (ft_eat(p))
				return (NULL);
	}
	return (NULL);
}

static int	ft_monitor(t_philo *p)
{
	pthread_mutex_lock(&p->state->eaten_philo_mutex);
	if (p->state->eaten_philo_count >= p->arg.num_philo)
		return (R_ERROR);
	pthread_mutex_unlock(&p->state->eaten_philo_mutex);
	pthread_mutex_lock(&p->state->print_mutex);
	pthread_mutex_lock(&p->state->life_mutex);
	if (ft_now(&p->state) - p->last_eating_time
		> (u_int64_t) p->arg.time_to_die)
	{
		printf("%llu %d %s\n", ft_now(&p->state), p->id, ft_get_status(DIED));
		return (R_ERROR);
	}
	pthread_mutex_unlock(&p->state->print_mutex);
	pthread_mutex_unlock(&p->state->life_mutex);
	return (R_SUCCESS);
}
