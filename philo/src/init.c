/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:46:12 by mochan            #+#    #+#             */
/*   Updated: 2022/09/08 21:32:15 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	init_philosophers(t_prgm *vars)
{
	int			i;

	i = 0;
	while (i < vars->nb_of_philos)
	{
		vars->philos[i].philo_id = i + 1;
		vars->philos[i].ttd = vars->time_to_die;
		vars->philos[i].tte = vars->time_to_eat;
		vars->philos[i].tts = vars->time_to_sleep;
		vars->philos[i].start_time = vars->start_time;
		vars->philos[i].fork_taken = 0;
		i++;
	}
}

static void	init_forks(t_prgm *vars)
{
	int				i;
	t_fork			tmp_fork;

	i = 0;
	while (i < vars->nb_of_philos)
	{
		// pthread_mutex_init(&vars->array_forks[i], NULL);
		tmp_fork.id = i + 1;
		pthread_mutex_init(&tmp_fork.mutex, NULL);
		vars->array_forks[i] = tmp_fork;
		i++;
	}
}

static void	assign_forks(t_prgm *vars)
{
	int			i;

	i = 0;
	while (i < vars->nb_of_philos)
	{
		vars->philos[i].right_fork = &vars->array_forks[i];
		if (i != vars->nb_of_philos - 1)
			vars->philos[i].left_fork = &vars->array_forks[i + 1];
		else if (i == vars->nb_of_philos - 1)
			vars->philos[i].left_fork = &vars->array_forks[0];
		i++;
	}
	i = 0;
	printf("========================================\n");
	printf("philosophers' forks\n");
	while (i < vars->nb_of_philos)
	{
		printf("philo %d has Rf %d and Lf %d.\n",
				vars->philos[i].philo_id,
				vars->philos[i].right_fork->id,
				vars->philos[i].left_fork->id);
		i++;
	}
	printf("========================================\n");
}

void	initialize(t_prgm *vars)
{
	init_philosophers(vars);
	init_forks(vars);
	assign_forks(vars);
}
