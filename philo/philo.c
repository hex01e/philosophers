/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:21:46 by houmanso          #+#    #+#             */
/*   Updated: 2023/06/16 15:02:05 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ff(void)
{
	system("leaks philo");
}

int	main(int ac, char *av[])
{
	t_info	*info;
	t_heap	*heap;
	t_philo	*philo;

	atexit(ff);
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
		if (is_died(philo, info))
			return (empty_trash(&heap), 0);
		if (info->times != -1 && done_yet(philo))
			return (empty_trash(&heap), 0);
		philo = philo->next;
	}
}
