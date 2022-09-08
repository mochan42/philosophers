/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:47 by mochan            #+#    #+#             */
/*   Updated: 2022/09/08 18:14:41 by mochan           ###   ########.fr       */
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
	long			ttd;
	long			tte;
	long			tts;
	long			ttt;
	long			start_time;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_prgm
{
	long			start_time;
	int				argc;
	char			**argv;
	int				nb_of_philos;
	int				nb_of_forks;
	// bool			continue_prgm; // 1 = continue prgm, 0 = stop prog.
	// pthread_t		death_supervisor;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_must_eat;
	t_philo			*philos;
	pthread_mutex_t	*array_forks;
}	t_prgm;

/* ########################################################################## */
/* CONSTANTS */

# define MAX_INT 2147483647

/* ########################################################################## */
/* FUNCTIONS */

/* check_input.c */
void		check_arg_is_digit(t_prgm	*vars);
void		check_input(t_prgm	*vars);
void		check_nb_arguments(t_prgm	*vars);
void		check_number_value(t_prgm *vars);

/* init.c */
void		initialize(t_prgm *vars);

/* routines.c */
void		eating(t_philo	*philo);
void		sleeping(t_philo *philo);
void		take_a_fork(t_philo	*philo);
void		thinking(t_philo *philo);

/* time.c */
long		get_time_ms(void);

/* utils_1.c */
int			my_isspace(char c);
int			ft_atoi(const char *str);

#endif