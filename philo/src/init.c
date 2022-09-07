/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:46:12 by mochan            #+#    #+#             */
/*   Updated: 2022/09/07 15:13:50 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void init_philosophers(t_prgm *vars)
{
	int			i;

	i = 0;
	while (i < vars->nb_of_philos)
	{
		vars->philos[i].philo_id = i + 1;
		i++;
	}
}

static void init_forks(t_prgm *vars)
{
	int			i;

	i = 0;
	while (i < vars->nb_of_philos)
	{
		pthread_mutex_init(&vars->array_forks[i], NULL);
		i++;
	}
}

static void assign_forks(t_prgm *vars)
{
	int			i;

	i = 0;
	while (i < vars->nb_of_philos)
	{
		vars->philos[i].right_fork = &vars->array_forks[i];
		if (i != vars->philos[i].philo_id)
			vars->philos[i].left_fork = &vars->array_forks[i+1];
		else if (i == vars->nb_of_philos)
			vars->philos[i].left_fork = &vars->array_forks[0];
		i++;
	}
}

void	initialize(t_prgm *vars)
{
	init_philosophers(vars);
	init_forks(vars);
	assign_forks(vars);
}
