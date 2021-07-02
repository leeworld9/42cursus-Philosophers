/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 04:10:25 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/02 10:54:00 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	param_parse(int argc, char **argv)
{
	g_data.number_of_philo = ft_atoi(argv[1]);
	g_data.time_to_die = ft_atoi(argv[2]);
	g_data.time_to_eat = ft_atoi(argv[3]);
	g_data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g_data.philo_must_eat = ft_atoi(argv[5]);
	else
		g_data.philo_must_eat = -1;
}

int		init(int argc, char **argv)
{
	int					i;
	unsigned long long	time;

	param_parse(argc, argv);
	pthread_mutex_init(&g_data.write, NULL); //??
	pthread_mutex_init(&g_data.lock, NULL); //??
	if ((g_data.philo = malloc(sizeof(t_philo) * g_data.number_of_philo)) == NULL)
		return (0);
	if ((g_data.fork = malloc(sizeof(t_fork) * g_data.number_of_philo)) == NULL)
		return (0);
	//g_data.state++;
	i = 0;
	time = gettime();
	while (i < g_data.number_of_philo)
	{
		g_data.philo[i].id = i;
		g_data.philo[i].last_eat_time = time;
		g_data.philo[i].total_eat = 0;
		pthread_mutex_init(&g_data.philo[i].lock, NULL); //? 필요?

		g_data.fork[i].id = i;
		g_data.fork[i].state = false;
		pthread_mutex_init(&g_data.fork[i].lock, NULL);
		i++;
	}
	return (1);
}