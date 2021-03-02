/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:20:52 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/01 17:56:11 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			*life_sikle(void *philo_elem)
{
	t_philo				*philo;

	philo = ((t_list *)philo_elem)->ph;
	while (philo->count_eat < philo->params.number_must_eat && philo->is_live
		&& !philo->always_life)
	{
		get_fork(philo);
		eating(philo);
		return_fork(philo);
		sleeping(philo);
		print_params(philo, THINKING);
	}
	return (NULL);
}

void			*check_life(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	sem_wait(philo->sem_check);
	sem_wait(philo->sem_check_eat);
	while (1)
	{
		if (philo->count_eat == philo->params.number_must_eat
			&& !philo->always_life)
		{
			philo->always_life = 1;
			sem_post(philo->sem_check_eat);
		}
		if (!philo->is_eating && !philo->always_life &&
			(long long int)(philo->time_to_die - get_time()) < 0)
		{
			sem_post(philo->sem_check);
			print_params(philo, DIED);
			philo->is_live = 0;
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

void			init_philo(t_list *root, t_global *g)
{
	root->ph->time = 0;
	root->ph->count_eat = 0;
	root->ph->is_live = 1;
	root->ph->params = g->params;
	root->next = NULL;
	root->ph->is_eating = 0;
	root->ph->semaphore = g->semaphore;
	root->ph->mutex_text = g->mutex_text;
	root->ph->always_life = 0;
	pthread_mutex_init(&root->ph->self, NULL);
	root->ph->time_to_die = g->time_die;
	root->ph->time_start = g->time_start;
	root->ph->sem_check = g->sem_check;
	root->ph->sem_check_eat = g->sem_check_eat;
}

int				create_processes(t_list *root)
{
	int			status;

	root->ph->pid = fork();
	if (root->ph->pid < 0)
		return (1);
	else if (root->ph->pid == 0)
	{
		status = pthread_create(&root->ph->monitor,
			NULL, &check_life, root->ph);
		if (status != 0)
			error_exit(ERROR_CREATE_THREAD);
		pthread_detach(root->ph->monitor);
		life_sikle(root);
		exit(0);
	}
	return (0);
}

int				create_philo(t_global *g, int i)
{
	t_list		*root;

	root = g->list;
	if (!root)
	{
		if (!(root = malloc(sizeof(t_list))))
			error_exit(ERROR_BAD_MALLOC);
		g->list = root;
	}
	else
	{
		while (root->next)
			root = root->next;
		if (!(root->next = malloc(sizeof(t_list))))
			error_exit(ERROR_BAD_MALLOC);
		root = root->next;
	}
	if (!(root->ph = malloc(sizeof(t_philo))))
		error_exit(ERROR_BAD_MALLOC);
	root->ph->number = i;
	init_philo(root, g);
	if (create_processes(root))
		error_exit(ERROR_CREATE_THREAD);
	return (0);
}
