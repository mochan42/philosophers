/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:34:28 by mochan            #+#    #+#             */
/*   Updated: 2022/09/07 17:48:55 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	check_nb_arguments(t_prgm	*vars)
{
	if (vars->argc < 5)
	{
		printf("Not enough arguments (min: 4).\n");
		exit (0);
	}
	else if (vars->argc > 6)
	{
		printf("Too many arguments (max: 5).\n");
		exit (0);
	}
}

void	check_arg_is_digit(t_prgm	*vars)
{
	int	i;
	int	j;

	i = 1;
	while (i < vars->argc)
	{
		j = 0;
		while (vars->argv[i][j] != '\0' )
		{
			if (vars->argv[i][j] == '-')
				j++;
			if (vars->argv[i][j] >= '0' && vars->argv[i][j] <= '9')
				j++;
			else
			{
				printf("Argument does not contain only digits.\n");
				exit (0);
			}
		}
		i++;
	}
}

void	check_number_value(t_prgm *vars)
{
	vars->nb_of_philos = ft_atoi(vars->argv[1]);
	vars->time_to_die = ft_atoi(vars->argv[2]);
	vars->time_to_eat = ft_atoi(vars->argv[3]);
	vars->time_to_sleep = ft_atoi(vars->argv[4]);
	if (vars->argc == 6)
		vars->number_must_eat = ft_atoi(
				vars->argv[5]);
	else
		vars->number_must_eat = -1;
	if (vars->nb_of_philos < 1 || vars->nb_of_philos > 200)
	{
		printf("error: number of philosophers must be between 1 and 200.\n");
		exit (0);
	}
	if (vars->time_to_die < 0 || vars->time_to_die > MAX_INT)
	{
		printf("error: time to die must be between 0 and 2147483647.\n");
		exit (0);
	}
	if (vars->time_to_eat < 0 || vars->time_to_eat > MAX_INT)
	{
		printf("error: time to eat must be between 0 and 2147483647.\n");
		exit (0);
	}
	if (vars->time_to_sleep < 0 || vars->time_to_sleep > MAX_INT)
	{
		printf("error: time to sleep must be between 0 and 2147483647.\n");
		exit (0);
	}
	if (vars->number_must_eat > MAX_INT)
	{
		printf("error: number_of_times_each_philosopher_must_eat must\
				 be less than 2147483647.\n");
		exit (0);
	}
}

void	check_input(t_prgm	*vars)
{
	check_nb_arguments(vars);
	check_arg_is_digit(vars);
	check_number_value(vars);
}
