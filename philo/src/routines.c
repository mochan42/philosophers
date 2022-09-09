/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:23:07 by mochan            #+#    #+#             */
/*   Updated: 2022/09/09 16:32:54 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_a_fork(t_philo	*philo)
{
	long			time;
	int				fork_to_take;

	if (philo->fork_taken == 0)
	{
		fork_to_take = philo->right_fork->id;
		philo->fork_taken = 1;
	}
	else
	{
		fork_to_take = philo->left_fork->id;
		philo->fork_taken = 0;
	}
	time = get_time_ms();
	printf("%10ld philo %d has taken a fork %d\n", time - philo->start_time,
		philo->philo_id, fork_to_take);
}

void	eating(t_philo	*philo)
{
	long	time;
	long	end_of_meal;

	time = get_time_ms();
	end_of_meal = time + philo->tte;
	pthread_mutex_lock(&philo->alive_mutex);
	philo->last_meal_time = end_of_meal;
	pthread_mutex_unlock(&philo->alive_mutex);
	printf("%10ld philo %d is eating\n",
		time - philo->start_time, philo->philo_id);
	while (get_time_ms() < end_of_meal)
		usleep(100);
}

void	sleeping(t_philo *philo)
{
	long	time;
	long	end_of_sleep;

	time = get_time_ms();
	end_of_sleep = time + philo->tts;
	printf("%10ld philo %d is sleeping\n",
		time - philo->start_time, philo->philo_id);
	while (get_time_ms() < end_of_sleep)
		usleep(100);
	time = get_time_ms();
}

void	thinking(t_philo *philo)
{
	long	time;
	long	end_of_thinking;

	time = get_time_ms();
	philo->ttt = (philo->ttd - (time - philo->last_meal_time)
			- philo->tte) / 2;
	printf("%10ld philo %d is thinking\n",
		time - philo->start_time, philo->philo_id);
	end_of_thinking = time + philo->ttt;
	while (get_time_ms() < end_of_thinking)
		usleep(100);
}
