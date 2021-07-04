/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 03:25:14 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/04 20:21:50 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long long	lock_fork(int act, int prev)
{
	unsigned long long	time;

	pthread_mutex_lock(&g_data.fork[prev].lock);
	time = gettime();
	g_data.fork[prev].state = true;
	msg(time, act, " has taken a fork\n", 18);
	if (g_data.number_of_philo != 1)
	{
		pthread_mutex_lock(&g_data.fork[act].lock);
		time = gettime();
		g_data.fork[act].state = true;
		msg(time, act, " has taken a fork\n", 18);
	}
	else
		pthread_mutex_unlock(&g_data.fork[prev].lock);
	return (time);
}

unsigned long long	eating(int act, int prev, unsigned long long time)
{
	g_data.ph[act].last_eat_time = time;
	msg(time, act, " is eating\n", 11);
	new_sleep(time, g_data.time_to_eat);
	g_data.fork[prev].state = false;
	g_data.fork[act].state = false;
	time = gettime();
	g_data.ph[act].total_eat++;
	pthread_mutex_unlock(&g_data.fork[prev].lock);
	pthread_mutex_unlock(&g_data.fork[act].lock);
	return (time);
}

void	sleeping(int act, unsigned long long time)
{
	msg(time, act, " is sleeping\n", 13);
	new_sleep(time, g_data.time_to_sleep);
}

void	thinking(int act)
{
	unsigned long long	time;

	time = gettime();
	msg(time, act, " is thinking\n", 13);
}

void	*thread(void *arg)
{
	int					act;
	int					prev;
	unsigned long long	time;

	act = *(int *)arg;
	prev = act - 1;
	if (prev == -1)
		prev = g_data.number_of_philo - 1;
	while (g_data.ph[act].state == true)
	{
		pthread_mutex_lock(&g_data.lock);
		if (g_data.fork[prev].state == false && g_data.fork[act].state == false)
		{
			time = lock_fork(act, prev);
			pthread_mutex_unlock(&g_data.lock);
			if (g_data.number_of_philo == 1)
				return (0);
			time = eating(act, prev, time);
			sleeping(act, time);
			thinking(act);
		}
		else
			pthread_mutex_unlock(&g_data.lock);
	}
	return (0);
}
