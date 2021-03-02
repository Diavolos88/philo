/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:50:41 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/02 15:04:39 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int				init_param(int argc, char *argv[], t_param *params)
{
	if (argc < 5 || argc > 6)
		return (1);
	params->number_of_philosophers = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (params->number_of_philosophers <= 1 || params->time_to_die <= 60
		|| params->time_to_eat <= 60 || params->time_to_sleep <= 60 ||
		params->number_of_philosophers >= 20)
		return (1);
	if (argc == 6)
		params->number_must_eat = ft_atoi(argv[5]);
	else
		params->number_must_eat = 99999999;
	return (0);
}

void			kill_all(t_global *g)
{
	t_list		*root;

	root = g->list;
	while (root)
	{
		root->ph->is_live = 0;
		root = root->next;
	}
}

void			init_global(t_global *g)
{
	int	i;

	i = -1;
	g->list = NULL;
	g->count_eat = 0;
	g->flag_death = 0;
	g->time_die = get_time() + g->params.time_to_die;
	gettimeofday(&(g->time_start), NULL);
	create_mutexes(g);
	while (++i < g->params.number_of_philosophers)
	{
		create_philo(g, i);
		usleep(1000);
	}
}

int				main(int argc, char *argv[])
{
	t_global			g;
	int					status;

	if (init_param(argc, argv, &(g.params)))
		error_exit(ERROR_WRONG_PARAMS);
	init_global(&g);
	status = pthread_create(&g.main_thread, NULL, &check_all, (void*)&g);
	if (status != 0)
		error_exit(ERROR_CREATE_THREAD);
	while (!g.flag_death && (g.count_eat != g.params.number_of_philosophers))
		usleep(10000);
	if (g.count_eat == g.params.number_of_philosophers)
	{
		sem_wait(g.mutex_text);
		write(1, "Everyone ate at least  ", 24);
		ft_putnbr(g.params.number_must_eat);
		write(1, " times\n", 8);
	}
	free_main(&g);
	return (0);
}
