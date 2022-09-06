/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:46:12 by mochan            #+#    #+#             */
/*   Updated: 2022/09/06 16:23:13 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void init_forks(t_prgm *vars, t_philo *philo)
{	
	philo->left_fork = malloc(sizeof(t_fork));
	philo->right_fork = malloc(sizeof(t_fork));

	philo->right_fork->fork_id = philo->philo_id;
	if (philo->philo_id != vars->nb_of_philos)
		philo->left_fork->fork_id = philo->philo_id + 1;
	else if (philo->philo_id == vars->nb_of_philos)
		philo->left_fork->fork_id = 1;
}

// static void init_forks(t_prgm *vars, t_philo *philo)
// {
// 	philo->right_fork_id = philo->philo_id;
// 	if (philo->philo_id != vars->nb_of_philos)
// 		philo->left_fork_id = philo->philo_id + 1;
// 	else if (philo->philo_id == vars->nb_of_philos)
// 		philo->left_fork_id = 1;
// }

static t_philo	**init_philosophers(t_prgm *vars)
{
	t_philo		**tab_philos;
	t_fork		*arr_forks;
	int			i;

	tab_philos = malloc(sizeof(t_philo *) * vars->nb_of_philos);
	if (!tab_philos)
		return (0);
	arr_forks = malloc(sizeof(t_fork *) * vars->nb_of_philos);
	if (!arr_forks)
		return (0);
	i = 1;
	while (i <= vars->nb_of_philos)
	{
		tab_philos[i] = malloc(sizeof(t_philo) * 1);
		tab_philos[i]->philo_id = i;
		init_forks(vars, tab_philos[i]);
		printf("philosopher %d : RIGHT fork number is %d.\n",
			tab_philos[i]->philo_id, tab_philos[i]->right_fork->fork_id);
		printf("philosopher %d : LEFT fork number is %d.\n",
			tab_philos[i]->philo_id, tab_philos[i]->left_fork->fork_id);
		i++;
	}
	// printf("==========================================================\n");
	return (tab_philos);
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
