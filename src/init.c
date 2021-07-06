/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 04:10:25 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/06 23:32:16 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	param_chk(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc < 5)
		return (0);
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
	}
	if (!param_parse(argc, argv))
		return (0);
	i = 0;
	while (++i < argc)
	{
		if (atoi(argv[i]) == 0)
			return (0);
	}
	return (1);
}

int	param_parse(int argc, char **argv)
{
	g_data.number_of_philo = ft_atoi(argv[1]);
	g_data.time_to_die = ft_atoi(argv[2]);
	g_data.time_to_eat = ft_atoi(argv[3]);
	g_data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g_data.philo_must_eat = ft_atoi(argv[5]);
	if (g_data.number_of_philo == -1 || g_data.time_to_die == -1)
		return (0);
	if (g_data.time_to_eat == -1 || g_data.time_to_sleep == -1)
		return (0);
	if (g_data.philo_must_eat == -1)
		return (0);
	return (1);
}

void	set_data(void)
{
	int	i;

	i = 0;
	g_data.start_time = gettime();
	while (i < g_data.number_of_philo)
	{
		g_data.ph[i].id = i;
		g_data.ph[i].last_eat_time = 0;
		g_data.ph[i].total_eat = 0;
		g_data.ph[i].state = true;
		g_data.fork[i].id = i;
		g_data.fork[i].state = false;
		pthread_mutex_init(&g_data.fork[i].lock, NULL);
		i++;
	}
}

int	init(void)
{
	pthread_mutex_init(&g_data.write, NULL);
	pthread_mutex_init(&g_data.chk_lock, NULL);
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
