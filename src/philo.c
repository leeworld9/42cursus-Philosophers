/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 22:59:00 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/05 00:45:10 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	must_eatchk(void)
{
	int	i;

	i = 0;
	while (i < g_data.number_of_philo)
	{
		if (g_data.ph[i].total_eat < g_data.philo_must_eat)
			return (false);
		i++;
	}
	return (true);
}

int	get_free(void)
{
	int	i;

	i = 0;
	while (i < g_data.number_of_philo)
		g_data.ph[i++].state = false;
	i = 0;
	while (i < g_data.number_of_philo)
		pthread_join(g_data.ph[i++].th, NULL);
	free(g_data.fork);
	free(g_data.ph);
	return (0);
}

int	end_check(int argc)
{
	int					i;
	unsigned long long	time;

	i = 0;
	time = gettime();
	pthread_mutex_lock(&g_data.chk_lock);
	while (i < g_data.number_of_philo)
	{
		if (g_data.ph[i].last_eat_time + g_data.time_to_die < time)
		{
			msg(time, i, " died\n", 6);
			return (get_free());
		}
		i++;
	}
	if (argc == 6 && must_eatchk())
		return (get_free());
	pthread_mutex_unlock(&g_data.chk_lock);
	return (1);
}

int	main(int argc, char **argv)
{
	int	i;

	if (!param_chk(argc, argv))
	{
		write(2, "Invalid Parameter Error\n", 24);
		return (0);
	}
	if (argc == 5 || argc == 6)
	{
		if (!init())
		{
			write(2, "Init Fail Error\n", 16);
			return (0);
		}
		i = 0;
		while (i < g_data.number_of_philo)
		{
			pthread_create(&g_data.ph[i].th, 0, thread, &g_data.ph[i].id);
			i++;
		}
		while (end_check(argc))
			continue ;
	}
	return (1);
}
