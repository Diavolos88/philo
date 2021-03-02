/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:41:50 by ealexa            #+#    #+#             */
/*   Updated: 2021/02/27 18:30:01 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

# define ERROR_WRONG_PARAMS			10
# define ERROR_BAD_MALLOC			12
# define ERROR_CREATE_THREAD		0
# define EATING						1
# define SLEEPING					2
# define THINKING					3
# define FORK						4
# define DIED						66

typedef struct			s_param
{
	int					time_to_sleep;
	int					time_to_eat;
	int					time_to_die;
	int					number_must_eat;
	int					number_of_philosophers;
}						t_param;

typedef struct			s_philo
{
	sem_t				*semaphore;
	pthread_mutex_t		*mutex_text;
	pthread_mutex_t		self;
	struct timeval		time_start;
	long long int		time_to_die;
	int					always_life;
	long long int		time;
	int					is_eating;
	int					number;
	int					count_eat;
	int					is_live;
	int					is_main;
	t_param				params;
	pthread_t			thread;
	pthread_t			monitor;
}						t_philo;

typedef struct			s_list
{
	t_philo				*ph;
	struct s_list		*next;
}						t_list;

typedef struct			s_global
{
	sem_t				*semaphore;
	pthread_mutex_t		*mutex_text;
	t_list				*list;
	t_param				params;
	int					status;
	long long int		time_die;
	struct timeval		time_start;
	pthread_t			main_thread;
}						t_global;

int						ft_atoi(const char *str);
void					print_params(t_philo *philo, int num);
float					time_diff(struct timeval time_start);
void					ft_putnbr(long long int n);
float					time_to_float(struct timeval time_start);
long long int			get_time(void);
void					ft_usleep(long long int m_sec);
void					error_exit(int err);
int						create_philo(t_global *g, int i);
void					eating(t_philo *philo);
void					sleeping(t_philo *philo);
void					get_fork(t_philo *philo);
void					return_fork(t_philo *philo);
void					error_exit(int err);
void					*check_all(void *g2);
void					create_mutexes(t_global *g);
void					free_main(t_global *g);
void					*check_all(void *g2);
void					create_mutexes(t_global *g);
void					free_main(t_global *g);
void					kill_all(t_global *g);

#endif
