/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 20:14:54 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/02 10:50:12 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int					id;
	unsigned long long	last_eat_time;
	int					total_eat;
	bool				state;
	pthread_mutex_t		lock; 
	pthread_t			thread; //스레드를 여기다 주는게 맞나?
}				t_philo;

typedef struct	s_fork
{
	int					id;
	bool				state;
	pthread_mutex_t		lock;
	//pthread_t			thread;
}				t_fork;

typedef struct	s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	//char			state;
	pthread_mutex_t	write; //?
	pthread_mutex_t	lock; //?
	t_philo			*philo;
	t_fork			*fork;
}				t_data;

t_data				g_data; // 전역변수

int	ft_atoi(const char *n);
int	ft_isdigit(int c);

int					init(int argc, char **argv);
void				*thread(void *arg);
unsigned long long	gettime(void);
void				ft_putnbr(unsigned long long n);
void				msg(unsigned long long time, int act, char *text, int len);
int					ft_str_is_numeric(char *str);


#endif