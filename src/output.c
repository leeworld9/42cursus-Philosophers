/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:04:19 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/07 00:58:06 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	msg(int act, char *text)
{
	pthread_mutex_lock(&g_data.write);
	if (g_data.ph[act].state == true)
		printf("%lldms %d %s", getworktime(), act + 1, text);
	pthread_mutex_unlock(&g_data.write);
}

void	dead_msg(int act, char *text, unsigned long long time)
{
	pthread_mutex_lock(&g_data.write);
	printf("%lldms %d %s", time, act + 1, text);
	pthread_mutex_unlock(&g_data.write);
}
