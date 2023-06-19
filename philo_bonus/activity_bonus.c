/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:40:46 by houmanso          #+#    #+#             */
/*   Updated: 2023/05/22 13:25:10 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	lets_exit(t_info *info, t_heap **heap)
{
	int	i;

	i = 0;
	sem_close(info->forks);
	sem_close(info->print);
	sem_close(info->done);
	sem_close(info->death);
	while (i < info->number)
		sem_close(info->philos[i++].last_sem);
	empty_trash(heap);
}

void	*status_synch(void *p)
{
	long	time;
	t_philo	*this;

	this = p;
	while (1)
	{
		sem_wait(this->last_sem);
		time = get_time(this->info);
		if (time - this->last_eat > this->info->death_time)
		{
			sem_wait(this->info->print);
			printf("%ld\t%d\t%s\n", get_time(this->info), this->id, "died.");
			sem_post(this->info->death);
			exit(0);
		}
		sem_post(this->last_sem);
		usleep(1500);
	}
}

void	activity(t_philo *this, t_info *info)
{
	int		i;

	i = 0;
	while (1)
	{
		sem_wait(info->forks);
		print(this, "has take a fork.");
		sem_wait(info->forks);
		print(this, "has take a fork.");
		sem_wait(this->last_sem);
		this->last_eat = get_time(this->info);
		sem_post(this->last_sem);
		print(this, "is eating.");
		nap(info->eating_time, this->info, this);
		sem_post(info->forks);
		sem_post(info->forks);
		print(this, "is sleeping.");
		nap(info->sleeping_time, this->info, this);
		print(this, "is thinking.");
		if (this->info->times > 0 && i++ == this->info->times)
			sem_post(this->info->done);
	}
}
