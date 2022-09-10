/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:44 by mochan            #+#    #+#             */
/*   Updated: 2022/09/10 19:17:29 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (philo->philo_id % 2)
			usleep(1000);
		pthread_mutex_lock(&philo->exit_flag_mutex);
		if (philo->exit_flag == 1)
		{
			pthread_mutex_unlock(&philo->exit_flag_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->exit_flag_mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		take_a_fork(philo);
		pthread_mutex_lock(&philo->left_fork->mutex);
		take_a_fork(philo);
		eating(philo);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*death_check(void *arg)
{
	t_prgm		*vars;
	int			ct[3];
	long		time;
	long		lifespan;

	vars = (t_prgm *) arg;
	ct[2] = vars->nb_of_philos;
	while (1)
	{
		time = get_time_ms();
		if (vars->nb_of_philos == 1)
		{
			pthread_mutex_lock(&vars->philos[0].exit_flag_mutex);
			vars->philos[0].exit_flag = 1;
			pthread_mutex_unlock(&vars->philos[0].exit_flag_mutex);
			printf("%10ld %d has taken a fork\n",
				get_time_ms() - vars->philos[0].start_time,
				vars->philos[0].philo_id);
			printf("%10ld %d died\n",
				get_time_ms() - vars->philos[0].start_time,
				vars->philos[0].philo_id);
			return (NULL);
		}
		ct[0] = 0;
		while (ct[0] < vars->nb_of_philos)
		{
			pthread_mutex_lock(&vars->philos[ct[0]].last_meal_mutex);
			lifespan = time - vars->philos[ct[0]].last_meal_time;
			if (vars->philos[ct[0]].number_must_eat == 0)
			{
				ct[2] -= 1;
				vars->philos[ct[0]].number_must_eat -= 1;
			}
			pthread_mutex_unlock(&vars->philos[ct[0]].last_meal_mutex);
			if (lifespan >= vars->philos->ttd || ct[2] == 0)
			{
				ct[1] = 0;
				while (ct[1] < vars->nb_of_philos)
				{
					pthread_mutex_lock(&vars->philos[ct[1]].exit_flag_mutex);
					vars->philos[ct[1]].exit_flag = 1;
					pthread_mutex_unlock(&vars->philos[ct[1]].exit_flag_mutex);
					ct[1] += 1;
				}
				if (ct[2] == 0)
					return (NULL);
				printf("%10ld %d died\n",
						get_time_ms() - vars->philos[0].start_time,
						vars->philos[0].philo_id);
				return (NULL);
			}
			ct[0] += 1;
		}
	}
	return (NULL);
}

void	create_threads(t_prgm *vars, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < vars->nb_of_philos)
	{
		if (pthread_create(&vars->philos[i].thread, NULL, &routine,
				&vars->philos[i]) != 0)
			perror("Failed to create thread.\n");
		i++;
	}
	if (pthread_create(thread, NULL, &death_check, vars) != 0)
		perror("Failed to create death supervisor thread.\n");
}

void	join_threads(t_prgm *vars, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < vars->nb_of_philos)
	{
		if (pthread_join(vars->philos[i].thread, NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	if (pthread_join(*thread, NULL) != 0)
		perror("Failed to join thread");
}

int	main(int argc, char **argv)
{
	t_prgm			philo_prgm;
	pthread_t		death_supervisor[1];

	philo_prgm.start_time = get_time_ms();
	philo_prgm.argc = argc;
	philo_prgm.argv = argv;
	check_input(&philo_prgm);
	philo_prgm.philos = malloc(sizeof(t_philo) * philo_prgm.nb_of_philos);
	if (!philo_prgm.philos)
		return (0);
	philo_prgm.array_forks = malloc(sizeof(t_fork)
			* philo_prgm.nb_of_philos);
	if (!philo_prgm.array_forks)
		return (0);
	initialize(&philo_prgm);
	create_threads(&philo_prgm, death_supervisor);
	join_threads(&philo_prgm, death_supervisor);
	destroy_mutexes(philo_prgm);
	return (0);
}
