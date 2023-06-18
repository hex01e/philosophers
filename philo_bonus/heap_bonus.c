/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:05:03 by houmanso          #+#    #+#             */
/*   Updated: 2023/05/20 18:05:07 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	add_to_heap(t_heap **heap, void *addr)
{
	t_heap	*new;

	if (heap)
	{
		new = malloc(sizeof(t_heap));
		if (!new)
			return (0);
		new->addr = addr;
		new->next = *heap;
		*heap = new;
	}
	return (1);
}

void	empty_trash(t_heap **heap)
{
	t_heap	*tmp;

	while (*heap)
	{
		tmp = *heap;
		if (tmp->addr)
			free(tmp->addr);
		*heap = (*heap)->next;
		free(tmp);
	}
	*heap = NULL;
}

void	*ft_malloc(size_t size, t_heap **heap)
{
	void	*p;

	p = malloc(size);
	if (!p)
		return (NULL);
	if (!add_to_heap(heap, p))
		return (NULL);
	return (p);
}
