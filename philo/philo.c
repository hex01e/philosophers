/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:21:46 by houmanso          #+#    #+#             */
/*   Updated: 2023/06/19 16:47:35 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	destroy(t_info *info, t_philo *p, t_heap **heap)
{
	int	j;

	j = 0;
	while (j++ < info->number)
	{
		pthread_mutex_destroy(&(p->fork));
		pthread_mutex_destroy(&(p->time));
		p = p->next;
	}
	pthread_mutex_destroy(&(info->mflag));
	pthread_mutex_destroy(&(info->print));
	empty_trash(heap);
	return (1);
}

int	main(int ac, char *av[])
{
	t_info	*info;
	t_heap	*heap;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (write(2, "no enaugh arrgament.", 21), 1);
	heap = NULL;
	philo = NULL;
	info = init_info(av, &heap);
	if (!info)
		return (printf("Error\n"), 1);
	info->begin = get_time(NULL);
	if (!setup_philos(&philo, info, &heap))
		return (printf("Error\n"), 1);
	while (philo)
	{
		usleep(1000);
		if (is_died(philo, info) || (info->times != -1 && done_yet(philo)))
		{
			pthread_mutex_lock(&(info->print));
			break ;
		}
		philo = philo->next;
	}
	destroy(info, philo, &heap);
}
