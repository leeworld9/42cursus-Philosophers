/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 20:14:54 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/07 00:58:15 by dohelee          ###   ########.fr       */
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

typedef struct s_philo
{
	int					id;
	unsigned long long	last_eat_time;
	int					total_eat;
	bool				state;
	pthread_t			th;
}				t_philo;

typedef struct s_fork
{
	int					id;
	bool				state;
	pthread_mutex_t		lock;
}				t_fork;

typedef struct s_data
{
	int					number_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					philo_must_eat;
	unsigned long long	start_time;
	pthread_mutex_t		write;
	pthread_mutex_t		chk_lock;
	t_philo				*ph;
	t_fork				*fork;
}				t_data;

t_data				g_data;

int					param_chk(int argc, char **argv);
int					param_parse(int argc, char **argv);
void				set_data(void);
int					init(void);

void				msg(int act, char *text);
void				dead_msg(int act, char *text, unsigned long long time);

bool				must_eatchk(void);
int					get_free(int id, bool died);
int					end_check(int argc);
int					main(int argc, char **argv);

unsigned long long	lock_fork(int id, int act, int prev);
unsigned long long	eating(int id, int act, int prev, unsigned long long time);
bool				fork_chk(int left, int right);
void				*thread(void *arg);

void				new_sleep(unsigned long long curr_time, int opt_time);
unsigned long long	getworktime(void);
unsigned long long	gettime(void);

int					ft_isdigit(int c);
int					ft_atoi(const char *n);
#endif