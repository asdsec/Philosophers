/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sademir <sademir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:15:12 by sademir           #+#    #+#             */
/*   Updated: 2024/03/07 16:45:49 by sademir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>

# define NOT_GIVEN -1

# define R_ERROR -1
# define R_SUCCESS 0

typedef struct s_arg_data
{
	int64_t	num_philo;
	int64_t	time_to_die;
	int64_t	time_to_eat;
	int64_t	time_to_sleep;
	int64_t	num_req_eat;
}	t_arg_data;

typedef int32_t	t_phid;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	TAKING_FORK,
	NONE
}	t_status;

struct			s_state;

typedef struct s_philo
{
	t_phid			id;
	pthread_t		th;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	t_arg_data		arg;
	struct s_state	*state;
	bool			is_first_loop;
	u_int64_t		last_eating_time;
	int32_t			eaten;
	bool			is_finish;
}	t_philo;

typedef struct s_state
{
	t_arg_data		arg;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		*threads;
	struct timeval	tv;
	u_int64_t		start_time;
	bool			is_odd_philos;
	int32_t			first_philo_count;
	pthread_mutex_t	first_philos_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	life_mutex;
	bool			life_ended;
	int32_t			eaten_philo_count;
	pthread_mutex_t	eaten_philo_mutex;
}	t_state;

int64_t		ft_atol(const char *str);
void		ft_dispose_state(t_state **state);
bool		ft_str_alldigit(const char *str);
int			ft_errmsg(int errcode, char *msg, t_state **state);
int			ft_init_state(t_state **s, int ac, char **av);
u_int64_t	ft_now(t_state **s);
void		ft_usleep(t_state **s, u_int64_t time);

void		ft_think_for_one_on_odd(t_philo *p);
bool		ft_is_finish_first_loop(t_philo *p);
void		ft_decrease_first_philos(t_philo *p);
bool		ft_safe_print(t_philo *p, t_status status);
char		*ft_get_status(t_status s);
bool		ft_eat(t_philo *p);
bool		ft_think(t_philo *p);

#endif