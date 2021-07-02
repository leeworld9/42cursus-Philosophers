/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 03:25:14 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/02 21:51:13 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				ft_putnbr(unsigned long long n)
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

void				msg(unsigned long long time, int act, char *text, int len)
{
	pthread_mutex_lock(&g_data.write); // 다른 lock쓰면 왜 안되지? 다른 프로세스도 동작중일지 모르니 더위에있는 lock 쓰는게 맞을듯
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(act + 1);
	write(1, text, len);
	pthread_mutex_unlock(&g_data.write);
}

/*
mutex 는 여러개의 쓰레드가 공유하는 데이타를 보호하기 위해서 사용되는 도구로써, 
보호하고자 하는 데이타를 다루는 코드영역을 단지 '한번에 하나의 쓰레드만' 실행가능 하도록 하는 방법으로 공유되는 데이타를 보호한다. 
이러한 코드영역(하나의 쓰레드만 점유가능한)을 critical section 이라고 하며, mutex 관련 API 를 이용해서 관리할수 있다.
*/

void				new_sleep(unsigned long long current_time, int optional_time)
{
	unsigned long long target_time;

	target_time = current_time + optional_time;
	while (target_time > gettime())
	{
		
	}
}

void				*thread(void *arg)
{
	int					act;
	int					prev;
	unsigned long long	time;

	act = *(int*)arg;
	prev = act - 1;
	if (prev == -1)
		prev = g_data.number_of_philo - 1;
	////////////////////////////////////
	//time = thread_lockfork(act, prev);
	while (1)
	{
		//현재 문제
		//mutex 때문인지 모르겠으나, 1개 필로소퍼 씩 먹는 경우가 있음. (동시에 먹어야되는데...)
		//mutex 때문에 그런거 맞음.... 두개 나눴을때 상황이조금 변화가 있음 (왼쪽 포크는 들개됨...)
		pthread_mutex_lock(&g_data.lock); // 이놈의 역할은?
		if (g_data.fork[prev].state == false && g_data.fork[act].state == false)
		{
		
			pthread_mutex_lock(&g_data.fork[prev].lock);
			time = gettime();
			g_data.fork[prev].state = true;
			msg(time, act, " has taken a fork left\n", 24); //left , 몇번째인지 기록하도록 수정하기

			pthread_mutex_lock(&g_data.fork[act].lock);
			time = gettime();
			g_data.fork[act].state = true;
			msg(time, act, " has taken a fork right\n", 25); //right
		pthread_mutex_unlock(&g_data.lock); 
			g_data.philo[act].last_eat_time = time;
			msg(time, act, " is eating\n", 11);

			new_sleep(time, g_data.time_to_eat);
			g_data.fork[prev].state = false;
			g_data.fork[act].state = false;
			time = gettime();
			g_data.philo[act].total_eat += g_data.time_to_eat;
			msg(time, act, " is sleeping\n", 13);

			pthread_mutex_unlock(&g_data.fork[prev].lock);
			pthread_mutex_unlock(&g_data.fork[act].lock);
			
			new_sleep(time, g_data.time_to_sleep);

			time = gettime();
			msg(time, act, " is thinking\n", 13);
		}
		else
			pthread_mutex_unlock(&g_data.lock);
	}
	return (0);
}
