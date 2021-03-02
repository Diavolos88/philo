/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:58:33 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/01 15:05:52 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(long long int n)
{
	long long int	nbr;

	if (n < 0)
	{
		ft_putchar('-');
		nbr = (unsigned long long int)(n * -1);
	}
	else
		nbr = n;
	if (nbr >= 10)
		ft_putnbr(nbr / 10);
	ft_putchar((char)(nbr % 10 + 48));
}

void	print_params(t_philo *philo, int num)
{
	if (philo->is_live || num == DIED)
	{
		sem_wait(philo->mutex_text);
		philo->time = time_diff(philo->time_start);
		ft_putnbr(philo->time);
		ft_putchar('\t');
		ft_putchar(' ');
		ft_putnbr(philo->number + 1);
		if (num == EATING)
			write(1, " is eating\n", 12);
		else if (num == SLEEPING)
			write(1, " is sleeping\n", 14);
		else if (num == THINKING)
			write(1, " is thinking\n", 14);
		else if (num == FORK)
			write(1, " has taken a fork\n", 19);
		else if (num == DIED)
			write(1, " died\n", 7);
		if (num != DIED)
			sem_post(philo->mutex_text);
	}
}

int		ft_atoi_check(long long int minus)
{
	if (minus == 1)
		return (-1);
	else
		return (0);
}

int		ft_atoi(const char *str)
{
	char			*tmp_str;
	size_t			i;
	long long int	res;
	long long int	res2;
	long long int	minus;

	minus = 1;
	res = 0;
	tmp_str = (char*)str;
	i = 0;
	while (tmp_str[i] == ' ' || tmp_str[i] == '\t' || tmp_str[i] == '\n'
	|| tmp_str[i] == '\v' || tmp_str[i] == '\f' || tmp_str[i] == '\r')
		i++;
	if (tmp_str[i] == '-' || tmp_str[i] == '+')
		if (tmp_str[i++] == '-')
			minus = -1;
	while (tmp_str[i] >= '0' && tmp_str[i] <= '9')
	{
		res2 = res;
		res = res * 10 + (tmp_str[i] - '0');
		if (res < res2)
			return (ft_atoi_check(minus));
		i++;
	}
	return (int)(minus * res);
}
