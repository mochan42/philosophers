/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:34:28 by mochan            #+#    #+#             */
/*   Updated: 2022/08/31 15:58:42 by mochan           ###   ########.fr       */
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

void	check_input(t_prgm	*vars)
{
	check_nb_arguments(vars);
	check_arg_is_digit(vars);
}
