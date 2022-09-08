/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:23:07 by mochan            #+#    #+#             */
/*   Updated: 2022/09/08 12:48:38 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_a_fork(t_philo	*philo)
{
	time_t	time;

	time = get_time_ms();
	printf("%10ld %d has taken a fork\n", time - philo->start_time,
		philo->philo_id);
}

void	eating(t_philo	*philo)
{
	time_t	time;
	time_t	end_of_meal;

	time = get_time_ms();
	end_of_meal = time + philo->tte;
	philo->last_meal_time = end_of_meal;
	printf("%10ld %d is eating\n", time - philo->start_time, philo->philo_id);
	while (get_time_ms() < end_of_meal)
	{
		usleep(500);
	}
}

void	sleeping(t_philo *philo)
{
	time_t	time;
	time_t	end_of_sleep;

	time = get_time_ms();
	end_of_sleep = time + philo->tts;
	printf("%10ld %d is sleeping\n", time - philo->start_time, philo->philo_id);
	while (get_time_ms() < end_of_sleep)
	{
		usleep(500);
	}
}

void	thinking(t_philo *philo)
{
	time_t	time;
	time_t	end_of_thinking;

	time = get_time_ms();
	philo->ttt = (philo->ttd - (time - philo->last_meal_time) - philo->tte)/2;
	printf("%10ld %d is thinking\n", time - philo->start_time, philo->philo_id);
	end_of_thinking = time + philo->ttt;
	while (get_time_ms() < end_of_thinking)
	{
		usleep(500);
	}
}
