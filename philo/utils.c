/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 08:09:15 by houmanso          #+#    #+#             */
/*   Updated: 2023/06/19 14:10:14 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_info *info)
{
	struct timeval	val;
	long			time;

	gettimeofday(&val, NULL);
	time = val.tv_sec * 1000 + val.tv_usec / 1000;
	if (info)
		time -= info->begin;
	return (time);
}

int	nap(long time, t_info *info, t_philo *this)
{
	long	old;
	int		flag;

	old = get_time(info) + this->id * 0;
	while (get_time(info) - old < time)
	{
		pthread_mutex_lock(&(info->mflag));
		flag = info->flag;
		pthread_mutex_unlock(&(info->mflag));
		if (flag)
			return (1);
		usleep(100);
	}
	return (0);
}

void	print(t_philo *this, char *msg)
{
	pthread_mutex_lock(&(this->info->print));
	printf("%ld\t%d\t%s\n", get_time(this->info), this->id, msg);
	pthread_mutex_unlock(&(this->info->print));
}

int	done_yet(t_philo *p)
{
	int	j;

	j = 0;
	while (j++ < p->info->number)
	{
		pthread_mutex_lock(&(p->time));
		if (p->done != DONE)
		{
			pthread_mutex_unlock(&(p->time));
			return (0);
		}
		pthread_mutex_unlock(&(p->time));
		p = p->next;
	}
	pthread_mutex_lock(&(p->info->mflag));
	p->info->flag = 1;
	pthread_mutex_unlock(&(p->info->mflag));
	return (1);
}

int	is_died(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&(philo->time));
	if ((get_time(info) - philo->last_eat > info->death_time))
	{
		pthread_mutex_lock(&(info->mflag));
		info->flag = 1;
		pthread_mutex_unlock(&(info->mflag));
		pthread_mutex_unlock(&(philo->time));
		print(philo, "is died.");
		return (1);
	}
	pthread_mutex_unlock(&(philo->time));
	return (0);
}
