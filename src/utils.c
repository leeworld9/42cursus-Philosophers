/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 20:13:30 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/06 23:48:19 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

static int	ft_limitchk(int nbr)
{
	if (INT_MAX < nbr)
		return (-1);
	else if (INT_MIN > nbr)
		return (-1);
	else
		return (nbr);
}

int	ft_atoi(const char *n)
{
	int			i;
	long long	sum;
	long long	chk;

	i = -1;
	sum = 0;
	chk = 1;
	while (ft_isspace(*n))
		n++;
	if (*n == '-' || *n == '+')
	{
		if (*n++ == '-')
			chk = -1;
	}
	while (n[++i] != '\0')
	{
		if (ft_isspace(n[i]) || !ft_isdigit(n[i]) || n[i] == '-' || n[i] == '+')
			return (ft_limitchk(sum * chk));
		sum = (sum * 10) + (n[i] - '0');
		if (INT_MAX < sum * chk)
			return (-1);
		else if (INT_MIN > sum * chk)
			return (-1);
	}
	return (sum * chk);
}
