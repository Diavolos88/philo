/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:36:39 by ealexa            #+#    #+#             */
/*   Updated: 2021/02/27 18:18:07 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void			eating(t_philo *philo)
{
	philo->is_eating = 1;
	print_params(philo, EATING);
	philo->time_to_die = get_time() + philo->params.time_to_die;
	ft_usleep(philo->params.time_to_eat);
	philo->count_eat += 1;
	philo->is_eating = 0;
}

void			sleeping(t_philo *philo)
{
	print_params(philo, SLEEPING);
	ft_usleep(philo->params.time_to_sleep);
}

void			get_fork(t_philo *philo)
{
	sem_wait(philo->semaphore);
	print_params(philo, FORK);
	sem_wait(philo->semaphore);
	print_params(philo, FORK);
}

void			return_fork(t_philo *philo)
{
	sem_post(philo->semaphore);
	sem_post(philo->semaphore);
}

void			error_exit(int err)
{
	if (err == ERROR_WRONG_PARAMS)
		write(1, "Error: wrong params!\n", 22);
	else if (err == ERROR_CREATE_THREAD)
		write(1, "Error: can't create thread!\n", 29);
	else if (err == ERROR_BAD_MALLOC)
		write(1, "Error: so bad malloc didn't get memory!\n", 41);
	exit(1);
}
