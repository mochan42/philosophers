/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:34:28 by mochan            #+#    #+#             */
/*   Updated: 2022/09/12 14:27:47 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	check_nb_arguments(t_prgm	*vars)
{
	if (vars->argc < 5)
	{
		printf("Not enough arguments (min: 4).\n");
		return (1);
	}
	else if (vars->argc > 6)
	{
		printf("Too many arguments (max: 5).\n");
		return (1);
	}
	else
		return (0);
}

int	check_arg_is_digit(t_prgm	*vars)
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
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_number_value_1(t_prgm *vars)
{
	if (vars->nb_of_philos < 1 || vars->nb_of_philos > 200)
	{
		printf("error: number of philosophers must be between 1 and 200.\n");
		return (1);
	}
	if (vars->time_to_die < 0 || vars->time_to_die > MAX_INT)
	{
		printf("error: time to die must be between 0 and 2147483647.\n");
		return (1);
	}
	if (vars->time_to_eat < 0 || vars->time_to_eat > MAX_INT)
	{
		printf("error: time to eat must be between 0 and 2147483647.\n");
		return (1);
	}
	if (vars->time_to_sleep < 0 || vars->time_to_sleep > MAX_INT)
	{
		printf("error: time to sleep must be between 0 and 2147483647.\n");
		return (1);
	}
	else
		return (0);
}

int	check_number_value_2(t_prgm *vars)
{
	if (vars->argc == 6 && (vars->number_must_eat > MAX_INT
			|| vars->number_must_eat < 0))
	{
		printf("error: number od meals must be >0 or less than 2147483647.\n");
		return (1);
	}
	if (vars->argc == 6 && vars->number_must_eat == 0)
	{
		printf("error: each philosopher should eat at least once.\n");
		return (1);
	}
	else
		return (0);
}

int	check_input(t_prgm	*vars)
{
	if (check_nb_arguments(vars) == 1)
		return (1);
	if (check_arg_is_digit(vars) == 1)
		return (1);
	retrieve_args(vars);
	if (check_number_value_1(vars) == 1)
		return (1);
	if (check_number_value_2(vars) == 1)
		return (1);
	else
		return (0);
}
