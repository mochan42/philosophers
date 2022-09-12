/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:06:10 by mochan            #+#    #+#             */
/*   Updated: 2022/09/12 14:14:07 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	stop_prgm(t_philo *philo)
{
	pthread_mutex_lock(&philo->exit_flag_mutex);
	if (philo->exit_flag == 1)
	{
		pthread_mutex_unlock(&philo->exit_flag_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->exit_flag_mutex);
	return (0);
}

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
	int	i;

	i = 0;
	while (i < vars.nb_of_philos)
	{
		pthread_mutex_destroy(&vars.array_forks[i].mutex);
		pthread_mutex_destroy(&vars.philos[i].last_meal_mutex);
		pthread_mutex_destroy(&vars.philos[i].exit_flag_mutex);
		i++;
	}
	pthread_mutex_destroy(&vars.printf_mutex);
}

void	retrieve_args(t_prgm *vars)
{
	vars->nb_of_philos = ft_atoi(vars->argv[1]);
	vars->time_to_die = ft_atoi(vars->argv[2]);
	vars->time_to_eat = ft_atoi(vars->argv[3]);
	vars->time_to_sleep = ft_atoi(vars->argv[4]);
	if (vars->argc == 6)
		vars->number_must_eat = ft_atoi(
				vars->argv[5]);
	else
		vars->number_must_eat = -1;
}
