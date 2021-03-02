/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:40:05 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/01 18:01:52 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		check_all_while(t_global *g, int *flag)
{
	t_list		*root;
	int			count;

	root = g->list;
	count = 0;
	while (root)
	{
		if (root->ph->always_life)
			count += 1;
		if (count == g->params.number_of_philosophers || !root->ph->is_live)
		{
			*flag = 0;
			if (count == g->params.number_of_philosophers)
			{
				pthread_mutex_lock(g->mutex_text);
				write(1, "Everyone ate at least  ", 24);
				ft_putnbr(g->params.number_must_eat);
				write(1, " times\n", 8);
			}
			kill_all(g);
			ft_usleep(1);
			break ;
		}
		root = root->next;
	}
}

void		*check_all(void *g2)
{
	t_global	*g;
	int			flag;

	g = (t_global *)g2;
	flag = 1;
	while (flag)
	{
		check_all_while(g, &flag);
		usleep(100);
	}
	return (NULL);
}

void		create_mutexes(t_global *g)
{
	int	i;

	i = -1;
	sem_unlink("school 21");
	g->semaphore = sem_open("school 21", O_CREAT, 0644,
		g->params.number_of_philosophers);
	g->mutex_text = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(&g->mutex_text[0], NULL);
}

void		free_main(t_global *g)
{
	t_list	*root;
	t_list	*tmp;

	root = g->list;
	sem_unlink("school 21");
	pthread_mutex_destroy(g->mutex_text);
	free(g->mutex_text);
	root = g->list;
	while (root)
	{
		tmp = root;
		pthread_mutex_destroy(&root->ph->self);
		free(root->ph);
		root = root->next;
		free(tmp);
	}
}
