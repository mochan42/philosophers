/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:47 by mochan            #+#    #+#             */
/*   Updated: 2022/09/12 14:24:06 by mochan           ###   ########.fr       */
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

typedef struct s_fork
{
	int					id;
	pthread_mutex_t		mutex;
}	t_fork;

typedef struct s_philo
{
	int				philo_id;
	long			ttd;
	long			tte;
	long			tts;
	long			ttt;
	long			number_must_eat;
	long			start_time;
	long			last_meal_time;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				fork_taken;
	int				exit_flag;
	pthread_mutex_t	*printf_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	exit_flag_mutex;
}	t_philo;

typedef struct s_prgm
{
	long			start_time;
	int				argc;
	char			**argv;
	int				nb_of_philos;
	int				nb_of_forks;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_must_eat;
	long			curr_time;
	int				ct[3];
	pthread_mutex_t	printf_mutex;
	t_philo			*philos;
	t_fork			*array_forks;
}	t_prgm;

/* ########################################################################## */
/* CONSTANTS */

# define MAX_INT 2147483647
# define TIME_LOST 20

/* ########################################################################## */
/* FUNCTIONS */

/* check_input.c */
int			check_arg_is_digit(t_prgm	*vars);
int			check_input(t_prgm	*vars);
int			check_nb_arguments(t_prgm	*vars);
int			check_number_value_1(t_prgm *vars);
int			check_number_value_2(t_prgm *vars);

/* death_management.c */
void		*death_routine(void *arg);

/* init.c */
void		initialize(t_prgm *vars);

/* routines.c */
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		take_forks(t_philo	*philo);
void		thinking(t_philo *philo);

/* time.c */
long		get_time_ms(void);

/* utils.c */
void		destroy_mutexes(t_prgm vars);
int			ft_atoi(const char *str);
int			my_isspace(char c);
void		retrieve_args(t_prgm *vars);
int			stop_prgm(t_philo *philo);

#endif