/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:50:41 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/02 15:03:33 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

int				main(int argc, char *argv[])
{
	t_global			g;
	int					i;
	int					status_addr;

	g.list = NULL;
	i = -1;
	if (init_param(argc, argv, &(g.params)))
		error_exit(ERROR_WRONG_PARAMS);
	create_mutexes(&g);
	g.time_die = get_time() + g.params.time_to_die;
	gettimeofday(&g.time_start, NULL);
	while (++i < g.params.number_of_philosophers)
	{
		if (i == 0)
			create_philo(&g, i, 0, g.params.number_of_philosophers - 1);
		else
			create_philo(&g, i, i - 1, i);
		usleep(1000);
	}
	pthread_create(&g.main_thread, NULL, &check_all, (void*)&g);
	i = pthread_join(g.main_thread, (void**)&status_addr);
	free_main(&g);
	return (0);
}
