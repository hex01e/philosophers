/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 07:46:59 by houmanso          #+#    #+#             */
/*   Updated: 2023/05/14 16:08:01 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_activity(t_philo *this)
{
	pthread_mutex_lock(&(this->fork));
	print(this, "has take a fork.");
	pthread_mutex_lock(&(this->next->fork));
	print(this, "has take a fork.");
	pthread_mutex_lock(&(this->time));
	this->last_eat = get_time(this->info);
	pthread_mutex_unlock(&(this->time));
	print(this, "is eating.");
	if (nap(this->info->eating_time, this->info, this))
		return (1);
	pthread_mutex_unlock(&(this->fork));
	pthread_mutex_unlock(&(this->next->fork));
	print(this, "is sleeping.");
	if (nap(this->info->sleeping_time, this->info, this))
		return (1);
	print(this, "is thinking.");
	return (0);
}

void	*activity(void *p)
{
	t_philo	*this;
	int		i;

	i = 0;
	this = p;
	if (this->id % 2)
		usleep(100);
	while (1)
	{
		if (do_activity(this))
			return (NULL);
		if (this->info->times != -1 && ++i == this->info->times)
		{
			pthread_mutex_lock(&(this->time));
			this->done = DONE;
			pthread_mutex_unlock(&(this->time));
		}
	}
}
