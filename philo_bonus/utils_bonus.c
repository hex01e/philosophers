/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 08:09:15 by houmanso          #+#    #+#             */
/*   Updated: 2023/05/20 20:22:00 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error(char *msg, t_heap **heap)
{
	printf("%s\n", msg);
	empty_trash(heap);
	exit(1);
}

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

void	nap(long time, t_info *info, t_philo *this)
{
	long	old;

	old = get_time(info) + this->id * 0;
	while (get_time(info) - old < time)
		usleep(100);
}

void	print(t_philo *this, char *msg)
{
	sem_wait(this->info->print);
	printf("%ld\t%d\t%s\n", get_time(this->info), this->id, msg);
	sem_post(this->info->print);
}

void	init_semphs(t_info *info, t_heap **heap)
{
	sem_unlink("/forks_sem");
	sem_unlink("/done_sem");
	sem_unlink("/print_sem");
	sem_unlink("/death_sem");
	info->forks = sem_open("/forks_sem", O_CREAT, 0644, info->number);
	info->done = sem_open("/done_sem", O_CREAT, 0644, 0);
	info->print = sem_open("/print_sem", O_CREAT, 0644, 1);
	info->death = sem_open("/death_sem", O_CREAT, 0644, 0);
	if (info->forks == SEM_FAILED || info->print == SEM_FAILED
		|| info->death == SEM_FAILED || info->done == SEM_FAILED)
		error("FAILED!", heap);
}
