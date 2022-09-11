/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:23:07 by mochan            #+#    #+#             */
/*   Updated: 2022/09/11 18:20:45 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_forks(t_philo	*philo)
{
	if (stop_prgm(philo) == 1)
		return ;
	pthread_mutex_lock(philo->printf_mutex);
	printf("%10ld %d has taken a fork\n", get_time_ms() - philo->start_time,
		philo->philo_id);
	printf("%10ld %d has taken a fork\n", get_time_ms() - philo->start_time,
		philo->philo_id);
	pthread_mutex_unlock(philo->printf_mutex);
}

////========below function used for debugging purposes===================
// void	take_a_fork(t_philo	*philo)
// {
// 	long			time;
// 	int				fork_to_take;

// 	pthread_mutex_lock(&philo->exit_flag_mutex);
// 	if (philo->exit_flag == 1)
// 	{
// 		pthread_mutex_unlock(&philo->exit_flag_mutex);
// 		return ;
// 	}
// 	pthread_mutex_unlock(&philo->exit_flag_mutex);
// 	if (philo->fork_taken == 0)
// 	{
// 		fork_to_take = philo->right_fork->id;
// 		philo->fork_taken = 1;
// 	}
// 	else
// 	{
// 		fork_to_take = philo->left_fork->id;
// 		philo->fork_taken = 0;
// 	}
// 	time = get_time_ms();
// 	printf("%10ld %d has taken a fork\n", time - philo->start_time,
// 		philo->philo_id);
// }

void	eating(t_philo	*philo)
{
	long	time;
	long	end_of_meal;

	time = get_time_ms();
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = get_time_ms();
	if (philo->number_must_eat > 0)
		philo->number_must_eat -= 1;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	end_of_meal = philo->tte + time;
	if (stop_prgm(philo) == 1)
		return ;
	pthread_mutex_lock(philo->printf_mutex);
	printf("%10ld %d is eating\n",
		time - philo->start_time, philo->philo_id);
	pthread_mutex_unlock(philo->printf_mutex);
	while (get_time_ms() < end_of_meal)
	{
		if (stop_prgm(philo) == 1)
			return ;
		usleep(100);
	}
}

void	sleeping(t_philo *philo)
{
	long	time;
	long	end_of_sleep;

	time = get_time_ms();
	end_of_sleep = time + philo->tts;
	if (stop_prgm(philo) == 1)
		return ;
	pthread_mutex_lock(philo->printf_mutex);
	printf("%10ld %d is sleeping\n",
		time - philo->start_time, philo->philo_id);
	pthread_mutex_unlock(philo->printf_mutex);
	while (get_time_ms() < end_of_sleep)
	{
		if (stop_prgm(philo) == 1)
			return ;
		usleep(100);
	}
}

void	thinking(t_philo *philo)
{
	long	time;
	long	end_of_thinking;

	time = get_time_ms();
	if (stop_prgm(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->ttt = (philo->ttd - (get_time_ms() - philo->last_meal_time)
			- philo->tte) / 2;
	if (philo->ttt < 0)
		philo->ttt = 0;
	if (philo->ttt > 600)
		philo->ttt = 200;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	end_of_thinking = time + philo->ttt;
	pthread_mutex_lock(philo->printf_mutex);
	printf("%10ld %d is thinking\n",
		time - philo->start_time, philo->philo_id);
	pthread_mutex_unlock(philo->printf_mutex);
	while (get_time_ms() < end_of_thinking)
	{
		if (stop_prgm(philo) == 1)
			return ;
		usleep(100);
	}
}
