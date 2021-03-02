/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:18:56 by ealexa            #+#    #+#             */
/*   Updated: 2021/02/27 16:57:45 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void				ft_usleep(long long int m_sec)
{
	long long int start;

	start = get_time();
	while (get_time() - start <= m_sec)
		usleep(100);
}

float				time_to_float(struct timeval time_start)
{
	return ((long long int)((time_start.tv_sec
	+ (time_start.tv_usec) / 1000000.0) * 1000));
}

float				time_diff(struct timeval time_start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((long long int)((end.tv_sec - time_start.tv_sec
	+ (end.tv_usec - time_start.tv_usec) / 1000000.0) * 1000.0));
}

long long int		get_time(void)
{
	struct timeval	time_start;

	gettimeofday(&time_start, NULL);
	return ((long long int)((time_start.tv_sec
	+ (time_start.tv_usec) / 1000000.0) * 1000.0));
}
