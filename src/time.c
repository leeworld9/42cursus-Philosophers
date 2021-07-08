/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 03:25:48 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/08 12:58:04 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	new_sleep(unsigned long long curr_time, int opt_time)
{
	unsigned long long	target_time;

	target_time = curr_time + opt_time;
	while (target_time > gettime())
	{
		usleep(100);
	}
}

unsigned long long	getworktime(void)
{
	unsigned long long	worktime;

	worktime = gettime() - g_data.start_time;
	return (worktime);
}

unsigned long long	gettime(void)
{
	struct timeval		time;
	unsigned long long	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}
