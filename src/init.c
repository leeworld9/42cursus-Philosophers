/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 04:10:25 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/04 07:55:02 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	param_parse(int argc, char **argv)
{
	g_data.number_of_philo = ft_atoi(argv[1]);
	g_data.time_to_die = ft_atoi(argv[2]);
	g_data.time_to_eat = ft_atoi(argv[3]);
	g_data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g_data.philo_must_eat = ft_atoi(argv[5]);
}

void	set_data(void)
{
	int					i;
	unsigned long long	time;

	i = 0;
	time = gettime();
	while (i < g_data.number_of_philo)
	{
		g_data.ph[i].id = i;
		g_data.ph[i].last_eat_time = time;
		g_data.ph[i].total_eat = 0;
		g_data.ph[i].state = true;
		g_data.fork[i].id = i;
		g_data.fork[i].state = false;
		pthread_mutex_init(&g_data.fork[i].lock, NULL);
		i++;
	}
}

int	init(int argc, char **argv)
{
	param_parse(argc, argv);
	pthread_mutex_init(&g_data.write, NULL);
	pthread_mutex_init(&g_data.lock, NULL);
	pthread_mutex_init(&g_data.must_chk, NULL);
	g_data.ph = malloc(sizeof(t_philo) * g_data.number_of_philo);
	if (g_data.ph == NULL)
		return (0);
	g_data.fork = malloc(sizeof(t_fork) * g_data.number_of_philo);
	if (g_data.fork == NULL)
	{
		free(g_data.ph);
		return (0);
	}
	set_data();
	return (1);
}
