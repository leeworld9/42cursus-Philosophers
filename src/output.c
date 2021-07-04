/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:04:19 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/04 20:37:20 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_putnbr(unsigned long long n)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

void	msg(unsigned long long time, int act, char *text, int len)
{
	pthread_mutex_lock(&g_data.write);
	if (g_data.ph[act].state == true)
	{
		ft_putnbr(time);
		write(1, " ", 1);
		ft_putnbr(act + 1);
		write(1, text, len);
	}
	pthread_mutex_unlock(&g_data.write);
}
