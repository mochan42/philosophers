/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:22:53 by mochan            #+#    #+#             */
/*   Updated: 2022/09/11 19:13:31 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	routine_one_philo(t_prgm *vars)
{
	long	time;

	time = get_time_ms();
	if (vars->nb_of_philos == 1)
	{
		pthread_mutex_lock(&vars->philos[0].exit_flag_mutex);
		vars->philos[0].exit_flag = 1;
		pthread_mutex_unlock(&vars->philos[0].exit_flag_mutex);
		pthread_mutex_lock(vars->philos[0].printf_mutex);
		printf("%10ld %d has taken a fork\n",
			time - vars->philos[0].start_time,
			vars->philos[0].philo_id);
		printf("%10ld %d died\n",
			vars->philos[0].ttd,
			vars->philos[0].philo_id);
		pthread_mutex_unlock(vars->philos[0].printf_mutex);
		return (1);
	}
	return (0);
}

static void	update_nb_eaten_meals(t_prgm *vars, long *life)
{
	pthread_mutex_lock(&vars->philos[vars->ct[0]].last_meal_mutex);
	*life = vars->curr_time - vars->philos[vars->ct[0]].last_meal_time;
	if (vars->philos[vars->ct[0]].number_must_eat == 0)
	{
		vars->ct[2] -= 1;
		vars->philos[vars->ct[0]].number_must_eat -= 1;
	}
	pthread_mutex_unlock(&vars->philos[vars->ct[0]].last_meal_mutex);
}

static int	check_if_philo_dies(t_prgm *vars, long life)
{
	if (life - TIME_LOST >= vars->philos->ttd || vars->ct[2] == 0)
	{
		vars->ct[1] = 0;
		while (vars->ct[1] < vars->nb_of_philos)
		{
			pthread_mutex_lock(&vars->philos[vars->ct[1]].exit_flag_mutex);
			vars->philos[vars->ct[1]].exit_flag = 1;
			pthread_mutex_unlock(&vars->philos[vars->ct[1]].exit_flag_mutex);
			vars->ct[1] += 1;
		}
		if (vars->ct[2] == 0)
			return (1);
		pthread_mutex_lock(vars->philos[vars->ct[0]].printf_mutex);
		printf("%10ld %d died\n",
			get_time_ms() - TIME_LOST - vars->philos[0].start_time,
			vars->philos[vars->ct[0]].philo_id);
		pthread_mutex_unlock(vars->philos[vars->ct[0]].printf_mutex);
		return (1);
	}
	return (0);
}

void	*death_routine(void *arg)
{
	t_prgm		*vars;
	long		lifespan;

	vars = (t_prgm *) arg;
	vars->ct[2] = vars->nb_of_philos;
	if (routine_one_philo(vars) == 1)
		return (NULL);
	while (1)
	{
		vars->curr_time = get_time_ms();
		vars->ct[0] = 0;
		while (vars->ct[0] < vars->nb_of_philos)
		{
			update_nb_eaten_meals(vars, &lifespan);
			if (check_if_philo_dies(vars, lifespan) == 1)
				return (NULL);
			vars->ct[0] += 1;
		}
	}
	return (NULL);
}
