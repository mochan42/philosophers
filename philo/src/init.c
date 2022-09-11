/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:46:12 by mochan            #+#    #+#             */
/*   Updated: 2022/09/11 17:33:57 by mochan           ###   ########.fr       */
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
		vars->philos[i].number_must_eat = vars->number_must_eat;
		vars->philos[i].start_time = vars->start_time;
		vars->philos[i].fork_taken = 0;
		vars->philos[i].exit_flag = 0;
		vars->philos[i].last_meal_time = vars->start_time;
		pthread_mutex_init(&vars->philos[i].last_meal_mutex, NULL);
		pthread_mutex_init(&vars->philos[i].exit_flag_mutex, NULL);
		pthread_mutex_init(&vars->array_forks[i].mutex, NULL);
		vars->philos[i].printf_mutex = &vars->printf_mutex;
		i++;
	}
}

static void	init_and_assign_forks(t_prgm *vars)
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
}

void	initialize(t_prgm *vars)
{
	pthread_mutex_init(&vars->printf_mutex, NULL);
	init_philosophers(vars);
	init_and_assign_forks(vars);
}
