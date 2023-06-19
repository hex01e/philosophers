/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:20:10 by houmanso          #+#    #+#             */
/*   Updated: 2023/06/19 13:42:02 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*new_node(int i, t_info *info, t_heap **heap)
{
	t_philo	*new;

	new = _malloc(sizeof(t_philo), heap);
	if (!new)
		return (NULL);
	new->id = i;
	new->done = BAD;
	new->info = info;
	new->next = NULL;
	new->last = NULL;
	new->last_eat = -1;
	if (pthread_mutex_init(&(new->fork), NULL) != 0)
		return (empty_trash(heap), NULL);
	if (pthread_mutex_init(&(new->time), NULL) != 0)
		return (empty_trash(heap), NULL);
	return (new);
}

static void	add_to_list(t_philo **philo, t_philo *new)
{
	t_philo	*last;

	if (!philo || !new)
		return ;
	if (*philo)
	{
		last = (*philo)->last;
		last->next = new;
		(*philo)->last = new;
		new->next = (*philo);
	}
	else
	{
		*philo = new;
		new->last = new;
		new->next = (*philo);
	}
}

int	setup_philos(t_philo **philo, t_info *info, t_heap **heap)
{
	t_philo	*new;
	int		i;

	i = 0;
	while (i++ < info->number)
	{
		new = new_node(i, info, heap);
		if (!new)
			return (empty_trash(heap), 0);
		add_to_list(philo, new);
		if (!philo)
			return (0);
	}
	i = 0;
	while (i++ < info->number)
	{
		if (pthread_create(&((*philo)->thread), NULL, activity, (*philo)) != 0)
			return (empty_trash(heap), 0);
		if (pthread_detach((*philo)->thread) != 0)
			return (empty_trash(heap), 0);
		(*philo) = (*philo)->next;
	}
	return (1);
}
