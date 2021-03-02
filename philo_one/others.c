/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:40:05 by ealexa            #+#    #+#             */
/*   Updated: 2021/02/27 18:31:13 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	g->mutex_arr = malloc(sizeof(pthread_mutex_t)
		* g->params.number_of_philosophers);
	while (++i < g->params.number_of_philosophers)
		pthread_mutex_init(&g->mutex_arr[i], NULL);
	g->mutex_text = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(&g->mutex_text[0], NULL);
}

void		free_main(t_global *g)
{
	t_list	*root;
	t_list	*tmp;
	int		i;

	i = -1;
	while (++i)
		pthread_mutex_destroy(&g->mutex_arr[i]);
	pthread_mutex_destroy(g->mutex_text);
	free(g->mutex_arr);
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
