/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:46:12 by mochan            #+#    #+#             */
/*   Updated: 2022/09/05 13:24:56 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static t_philo	**init_philosophers(t_prgm *vars)
{
	t_philo		**tab;
	int			i;

	tab = malloc(sizeof(t_philo) * vars->nb_of_philos);
	if (!tab)
		return (0);
	i = 1;
	while (i <= vars->nb_of_philos)
	{
		tab[i] = malloc(sizeof(t_philo) * 1);
		tab[i]->philo_id = i;
		i++;
	}
	return (tab);
}

void	initialize(t_prgm *vars)
{
	vars->nb_of_philos = ft_atoi(vars->argv[1]);
	vars->time_to_die = ft_atoi(vars->argv[2]);
	vars->time_to_eat = ft_atoi(vars->argv[3]);
	vars->time_to_sleep = ft_atoi(vars->argv[4]);
	if (vars->argc == 6)
		vars->number_must_eat = ft_atoi(
				vars->argv[5]);
	else
		vars->number_must_eat = 0;
	vars->philos = init_philosophers(vars);
}
