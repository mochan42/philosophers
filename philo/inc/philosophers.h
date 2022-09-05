/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:47 by mochan            #+#    #+#             */
/*   Updated: 2022/09/05 13:34:01 by mochan           ###   ########.fr       */
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
# include <sys/time.h>

/* ########################################################################## */
/* STRUCTURES */

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread;
	int				left_fork_id;
	int				right_fork_id;
}	t_philo;

typedef struct s_prgm
{
	time_t			start_time;
	int				argc;
	char			**argv;
	int				nb_of_philos;
	int				nb_of_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	t_philo			**philos;
}	t_prgm;

/* ########################################################################## */
/* CONSTANTS */

/* ########################################################################## */
/* FUNCTIONS */

/* check_input.c */
void		check_arg_is_digit(t_prgm	*vars);
void		check_input(t_prgm	*vars);
void		check_nb_arguments(t_prgm	*vars);

/* init.c */
void		initialize(t_prgm *vars);

/* utils_1.c */
int			my_isspace(char c);
int			ft_atoi(const char *str);

#endif