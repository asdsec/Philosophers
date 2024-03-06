/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sademir <sademir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:56:06 by sademir           #+#    #+#             */
/*   Updated: 2024/03/06 21:01:03 by sademir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

static void	ft_init_arg(t_state *s, int ac, char **av);
static int	ft_init_forks(t_state *s);
static int	ft_init_philos(t_state *s);
static void	ft_init_philo(t_state *s, pthread_t *ths, int32_t i);

int	ft_init_state(t_state **s, int ac, char **av)
{
	*s = (t_state *) malloc(sizeof(t_state));
	if (!*s)
		return (ft_errmsg(3, "state cannot be allocated", NULL));
	ft_init_arg(*s, ac, av);
	if (ft_init_forks(*s) != R_SUCCESS)
		return (ft_errmsg(4, "forks cannot be initialized", s));
	if (ft_init_philos(*s) != R_SUCCESS)
		return (ft_errmsg(5, "philos cannot be initialized", s));
	pthread_mutex_init(&(*s)->print_mutex, NULL);
	(*s)->first_philo_count = (*s)->arg.num_philo;
	pthread_mutex_init(&(*s)->first_philos_mutex, NULL);
	pthread_mutex_init(&(*s)->life_mutex, NULL);
	pthread_mutex_init(&(*s)->eaten_philo_mutex, NULL);
	(*s)->eaten_philo_count = 0;
	(*s)->life_ended = false;
	(*s)->is_odd_philos = (*s)->arg.num_philo % 2 == 1;
	return (R_SUCCESS);
}

static void	ft_init_arg(t_state *s, int ac, char **av)
{
	s->arg.num_philo = ft_atol(av[1]);
	s->arg.time_to_die = ft_atol(av[2]);
	s->arg.time_to_eat = ft_atol(av[3]);
	s->arg.time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		s->arg.num_req_eat = ft_atol(av[5]);
	else
		s->arg.num_req_eat = NOT_GIVEN;
}

static int	ft_init_forks(t_state *s)
{
	pthread_mutex_t	*mutexes;
	int				i;

	mutexes = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * s->arg.num_philo);
	if (!mutexes)
		return (R_ERROR);
	i = 0;
	while (i < s->arg.num_philo)
	{
		pthread_mutex_init(mutexes + i, NULL);
		i++;
	}
	s->forks = mutexes;
	return (R_SUCCESS);
}

static int	ft_init_philos(t_state *s)
{
	pthread_t	*ths;
	int32_t		i;

	s->philos = (t_philo *) malloc(sizeof(t_philo) * s->arg.num_philo);
	if (!s->philos)
		return (R_ERROR);
	ths = (pthread_t *) malloc(sizeof(pthread_t) * s->arg.num_philo);
	if (!ths)
		return (free(&s->philos), R_ERROR);
	i = 0;
	while (i < s->arg.num_philo)
	{
		ft_init_philo(s, ths, i);
		if (s->arg.num_philo == 1)
			break ;
		if (i == 0)
			s->philos[i].left = &s->forks[s->arg.num_philo - 1];
		else
			s->philos[i].left = &s->forks[i - 1];
		i++;
	}
	return (R_SUCCESS);
}

static void	ft_init_philo(t_state *s, pthread_t *ths, int32_t i)
{
	s->philos[i].id = (t_phid) i + 1;
	s->philos[i].right = &s->forks[i];
	s->philos[i].left = NULL;
	s->philos[i].th = ths[i];
	s->philos[i].arg = s->arg;
	s->philos[i].state = s;
	s->philos[i].is_first_loop = true;
	s->philos[i].last_eating_time = 0;
	s->philos[i].eaten = 0;
	s->philos[i].is_finish = false;
}
