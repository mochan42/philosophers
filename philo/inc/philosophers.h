/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:47 by mochan            #+#    #+#             */
/*   Updated: 2022/08/31 16:15:12 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ########################################################################## */
/* INCLUDES */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

/* ########################################################################## */
/* STRUCTURES */

typedef struct s_prgm
{
	int		argc;
	char	**argv;
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
}				t_prgm;

/* ########################################################################## */
/* CONSTANTS */

/* ########################################################################## */
/* FUNCTIONS */

/* check_input.c */
void		check_arg_is_digit(t_prgm	*vars);
void		check_input(t_prgm	*vars);
void		check_nb_arguments(t_prgm	*vars);

/* utils_1.c */
int			my_isspace(char c);
int			ft_atoi(const char *str);

#endif