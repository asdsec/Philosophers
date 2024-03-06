/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sademir <sademir@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:43:54 by sademir           #+#    #+#             */
/*   Updated: 2024/03/06 21:11:38 by sademir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "philo.h"

void	ft_dispose_state(t_state **state)
{
	if (!state)
		return ;
	free((*state)->forks);
	free((*state)->philos);
	free(*state);
	*state = NULL;
}

int	ft_errmsg(int errcode, char *msg, t_state **state)
{
	ft_dispose_state(state);
	printf("error (%d): %s\n", errcode, msg);
	return (errcode);
}
