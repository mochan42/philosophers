/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:23:07 by mochan            #+#    #+#             */
/*   Updated: 2022/09/10 18:54:44 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_a_fork(t_philo	*philo)
{
	long			time;
	int				fork_to_take;
	
	pthread_mutex_lock(&philo->exit_flag_mutex);
	if (philo->exit_flag == 1)
	{
		pthread_mutex_unlock(&philo->exit_flag_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->exit_flag_mutex);
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
	printf("%10ld %d has taken a fork\n", time - philo->start_time,
		philo->philo_id);
}

void	eating(t_philo	*philo)
{
	long	time;
	long	end_of_meal;

	time = get_time_ms();
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	end_of_meal = philo->tte + time;
	pthread_mutex_lock(&philo->exit_flag_mutex);
	if (philo->exit_flag == 1)
	{
		pthread_mutex_unlock(&philo->exit_flag_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->exit_flag_mutex);
	printf("%10ld %d is eating\n",
		time - philo->start_time, philo->philo_id);
	while (get_time_ms() < end_of_meal)
	{
		pthread_mutex_lock(&philo->exit_flag_mutex);
		if (philo->exit_flag == 1)
		{
			pthread_mutex_unlock(&philo->exit_flag_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->exit_flag_mutex);
		usleep(100);
	}
}

void	sleeping(t_philo *philo)
{
	long	time;
	long	end_of_sleep;

	time = get_time_ms();
	end_of_sleep = time + philo->tts;
	pthread_mutex_lock(&philo->exit_flag_mutex);
	if (philo->exit_flag == 1)
	{
		pthread_mutex_unlock(&philo->exit_flag_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->exit_flag_mutex);
	printf("%10ld %d is sleeping\n",
		time - philo->start_time, philo->philo_id);
	while (get_time_ms() < end_of_sleep)
	{
		pthread_mutex_lock(&philo->exit_flag_mutex);
		if (philo->exit_flag == 1)
		{
			pthread_mutex_unlock(&philo->exit_flag_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->exit_flag_mutex);
		usleep(100);
	}
}

void	thinking(t_philo *philo)
{
	long	time;
	long	end_of_thinking;

	time = get_time_ms();
	pthread_mutex_lock(&philo->exit_flag_mutex);
	if (philo->exit_flag == 1)
	{
		pthread_mutex_unlock(&philo->exit_flag_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->exit_flag_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->ttt = (philo->ttd - (time - philo->last_meal_time)
			- philo->tte) / 2;
	if (philo->ttt < 0)
		philo->ttt = 0;
	if (philo->ttt > 600)
		philo->ttt = 200;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	printf("%10ld %d is thinking\n",
		time - philo->start_time, philo->philo_id);
	end_of_thinking = time + philo->ttt;
	while (get_time_ms() < end_of_thinking)
	{
		pthread_mutex_lock(&philo->exit_flag_mutex);
		if (philo->exit_flag == 1)
		{
			pthread_mutex_unlock(&philo->exit_flag_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->exit_flag_mutex);
		usleep(100);
	}
}
