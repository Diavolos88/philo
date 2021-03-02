/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:40:05 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/01 17:57:19 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		*check_all_eat(void *g2)
{
	t_global	*g;

	g = (t_global *)g2;
	while (1)
	{
		sem_wait(g->sem_check_eat);
		g->count_eat += 1;
		if (g->count_eat == g->params.number_of_philosophers)
			break ;
	}
	return (NULL);
}

void		*check_all(void *g2)
{
	t_global	*g;
	pthread_t	thread;

	g = (t_global *)g2;
	pthread_create(&thread, NULL, check_all_eat, g2);
	pthread_detach(thread);
	sem_wait(g->sem_check);
	g->flag_death = 1;
	return (NULL);
}

void		create_mutexes(t_global *g)
{
	int	i;

	i = -1;
	sem_unlink("school 21");
	g->semaphore = sem_open("school 21", O_CREAT, 0644,
		g->params.number_of_philosophers);
	sem_unlink("text");
	g->mutex_text = sem_open("text", O_CREAT, 0644, 1);
	sem_unlink("school 42");
	g->sem_check = sem_open("school 42", O_CREAT, 0644,
		g->params.number_of_philosophers);
	sem_unlink("123123123123123123");
	g->sem_check_eat = sem_open("123123123123123123", O_CREAT, 0644,
		g->params.number_of_philosophers);
}

void		free_main(t_global *g)
{
	t_list	*root;
	t_list	*tmp;
	int		i;

	i = -1;
	sem_close(g->mutex_text);
	root = g->list;
	while (root)
	{
		kill(root->ph->pid, SIGKILL);
		tmp = root;
		pthread_mutex_destroy(&root->ph->self);
		free(root->ph);
		root = root->next;
		free(tmp);
	}
}
