/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:44 by mochan            #+#    #+#             */
/*   Updated: 2022/09/06 20:02:21 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	pthread_mutex_t	mutex_right_fork;
	pthread_mutex_t	mutex_left_fork;
	
	pthread_mutex_init(&mutex_right_fork, NULL);
	pthread_mutex_init(&mutex_left_fork, NULL);
	philo = (t_philo *) arg;
	pthread_mutex_lock(&mutex_right_fork);
	philo->right_fork->fork_status = 1;
	printf("%d has taken a fork\n", philo->philo_id);
	pthread_mutex_lock(&mutex_left_fork);
	philo->left_fork->fork_status = 1;
	printf("%d has taken a fork\n", philo->philo_id);
	if (philo->right_fork->fork_status == 1 && philo->left_fork->fork_status == 1)
		printf("%d is eating\n", philo->philo_id);
	printf("philo %d has Rf : %d (status: %d) and Lf id : %d (status : %d)\n", philo->philo_id, philo->right_fork->fork_id, philo->right_fork->fork_status, philo->left_fork->fork_id, philo->left_fork->fork_status);
	printf("=================================================================\n");
	philo->right_fork->fork_status = 0;
	philo->left_fork->fork_status = 0;
	pthread_mutex_unlock(&mutex_right_fork);
	pthread_mutex_unlock(&mutex_left_fork);
	pthread_mutex_destroy(&mutex_right_fork);
	pthread_mutex_destroy(&mutex_left_fork);
	// printf("%d is sleeping\n", philo->philo_id);
	// printf("%d is thinking\n", philo->philo_id);
	return (NULL);
}

void	create_threads(t_prgm *vars)
{
	int			i;
	
	i = 1;
	while (i <= vars->nb_of_philos)
	{
		if (pthread_create(&vars->philos[i]->thread, NULL, &routine,
				vars->philos[i]) != 0)
			perror("Failed to create thread");
		i++;
	}
}

void	join_threads(t_prgm *vars)
{
	int			i;

	i = 1;
	while (i <= vars->nb_of_philos)
	{
		if (pthread_join(vars->philos[i]->thread, NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_prgm		philo;

	philo.argc = argc;
	philo.argv = argv;
	check_input(&philo);
	initialize(&philo);
	create_threads(&philo);
	join_threads(&philo);
	return (0);
}
