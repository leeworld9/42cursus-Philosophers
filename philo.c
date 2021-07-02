#include "philo.h"


int		param_chk(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_str_is_numeric(char *str)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}


// int		endofprog(void)
// {
// 	if (g_data.state >= 1)
// 		free(g_data.philo);
// 	return (0);
// }

int		main_do(int argc)
{
	int					i;
	char				eat;
	unsigned long long	time;

	i = -1;
	time = gettime();
	eat = 1;
	//pthread_mutex_lock(&g_data.lock); // 내가 추가한것.. 필요하나?
	while (++i < g_data.number_of_philo)
	{
		if (argc == 6 && eat == 1 && g_data.philo[i].total_eat < g_data.philo_must_eat)
			eat = 0;
		if (g_data.philo[i].last_eat_time + g_data.time_to_die < time)
		{
			msg(time, i, " died\n", 6);
			//return (endofprog());
			return 0;
		}
	}
	//pthread_mutex_unlock(&g_data.lock);

	pthread_mutex_lock(&g_data.write);
	if (argc == 6 && eat == 1)
		return 0;
		//return (endofprog());
	pthread_mutex_unlock(&g_data.write);
	return (1);
}

int		main(int argc, char **argv)
{
	int i;
	//g_data.state = 0;

	if (!param_chk(argc, argv))
		return (-1);
	if (argc == 5 || argc == 6)
	{
		init(argc, argv);
		i = 0;
		while (i < g_data.number_of_philo)
		{
			pthread_create(&g_data.philo[i].thread, NULL, thread, (void *)&g_data.philo[i].id);
			i++;
		}
		while (1)
		{
			if (main_do(argc) == 0)
				break ;
		}
	}

	return (0);
}
