/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:42:44 by mochan            #+#    #+#             */
/*   Updated: 2022/09/06 17:20:31 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


int	check_if_forks_are_free(t_philo *philo);
{
	int	forks_are_free;

	forks_are_free = 0
	if (philo->left_fork->fork_status == 0 && philo->right_fork->fork_status == 0)
		forks_are_free = 1;
	else
		forks_are_free = 0;
	return (forks_in_use);
}
