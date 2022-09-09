/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:06:10 by mochan            #+#    #+#             */
/*   Updated: 2022/09/09 23:33:28 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	my_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r')
		return (1);
	else if (c == '\f' || c == '\v' || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (my_isspace(*str))
		str++;
	if (*str == '-')
	{
		negative = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		res = (res * 10) + (*str++ - 48);
	return (negative * res);
}

void	destroy_mutexes(t_prgm vars)
{
	int i;

	i = 0;
	while (i < vars.nb_of_philos)
	{
		pthread_mutex_destroy(&vars.philos[i].right_fork->mutex);
		pthread_mutex_destroy(&vars.philos[i].left_fork->mutex);
		pthread_mutex_destroy(&vars.philos[i].last_meal_mutex);
		pthread_mutex_destroy(&vars.philos[i].exit_flag_mutex);
		i++;
	}
}
