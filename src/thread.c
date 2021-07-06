/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 03:25:14 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/07 01:01:49 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long long	lock_fork(int id, int right, int left)
{
	g_data.fork[left].state = true;
	msg(id, "has taken a fork\n");
	if (g_data.number_of_philo != 1)
	{
		g_data.fork[right].state = true;
		msg(id, "has taken a fork\n");
	}
	else
	{
		g_data.fork[left].state = false;
		pthread_mutex_unlock(&g_data.fork[left].lock);
	}
	return (getworktime());
}

unsigned long long	eating(int id, int right, int left, unsigned long long time)
{
	g_data.ph[id].last_eat_time = time;
	msg(id, "is eating\n");
	new_sleep(gettime(), g_data.time_to_eat);
	g_data.fork[right].state = false;
	pthread_mutex_unlock(&g_data.fork[right].lock);
	g_data.fork[left].state = false;
	pthread_mutex_unlock(&g_data.fork[left].lock);
	g_data.ph[id].total_eat++;
	return (getworktime());
}

bool	fork_chk(int left, int right)
{
	pthread_mutex_lock(&g_data.fork[left].lock);
	if (g_data.fork[left].state != false)
	{
		pthread_mutex_unlock(&g_data.fork[left].lock);
		return (false);
	}
	else
	{
		if (g_data.number_of_philo != 1)
		{
			pthread_mutex_lock(&g_data.fork[right].lock);
			if (g_data.fork[right].state != false)
			{
				pthread_mutex_unlock(&g_data.fork[left].lock);
				pthread_mutex_unlock(&g_data.fork[right].lock);
				return (false);
			}
		}	
	}
	return (true);
}

void	*thread(void *arg)
{
	int					id;
	int					right;
	int					left;
	unsigned long long	time;

	id = *(int *)arg;
	right = id;
	left = right - 1;
	if (left == -1)
		left = g_data.number_of_philo - 1;
	while (g_data.ph[right].state == true)
	{
		if (!fork_chk(left, right))
			continue ;
		time = lock_fork(id, right, left);
		if (g_data.number_of_philo == 1)
			break ;
		time = eating(id, right, left, time);
		msg(id, "is sleeping\n");
		new_sleep(gettime(), g_data.time_to_sleep);
		time = getworktime();
		msg(id, "is thinking\n");
	}
}
