/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 03:25:48 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/04 20:39:21 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	new_sleep(unsigned long long current_time, int optional_time)
{
	unsigned long long	target_time;

	target_time = current_time + optional_time;
	while (target_time > gettime())
		continue ;
}

unsigned long long	gettime(void)
{
	struct timeval		time;
	unsigned long long	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}
