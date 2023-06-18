/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:25:32 by houmanso          #+#    #+#             */
/*   Updated: 2023/05/22 13:25:04 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*deid_yet(void	*p)
{
	t_info	*info;
	int		i;

	i = 0;
	info = (t_info *) p;
	sem_wait(info->death);
	while (i < info->number)
		kill(info->philos[i++].pid, SIGKILL);
	empty_trash(info->heap);
	exit(0);
}

void	setup_philo(t_philo *philo, t_info *info, t_heap **heap)
{
	if (philo->id % 2)
		usleep(100);
	if (pthread_create(&philo->thread, NULL, status_synch, philo) != 0
		|| philo->last_sem == SEM_FAILED)
		error("FAILED", heap);
	activity(philo, info);
}

void	init_philos(t_philo *philo, t_info *info, t_heap **heap)
{
	int	i;

	i = 0;
	while (i < info->number)
	{
		philo[i].info = info;
		philo[i].last_eat = 0;
		philo[i].id = i + 1;
		gen_name(&philo[i], "last_sem", heap);
		sem_unlink(philo[i].name);
		philo[i].last_sem = sem_open(philo[i].name, O_CREAT, 0644, 1);
		gen_name(&philo[i], "lock", heap);
		philo[i].lock = sem_open(philo[i].name, O_CREAT, 0644, 1);
		i++;
	}
}

void	run_childs(t_info *info, t_heap **heap)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = ft_malloc(sizeof(t_philo) * info->number, heap);
	if (!philo)
		error("error", heap);
	init_philos(philo, info, heap);
	i = 0;
	info->philos = philo;
	info->begin = get_time(NULL);
	while (i < info->number)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			setup_philo(&philo[i], info, heap);
		i++;
	}
}

int	main(int ac, char *av[])
{
	t_info	*info;
	t_heap	*heap;
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (write(2, "Error\n", 6), 1);
	heap = NULL;
	info = init_info(av, &heap);
	if (!info)
		error("FAILED!\n", &heap);
	info->heap = &heap;
	init_semphs(info, &heap);
	run_childs(info, &heap);
	pthread_create(&info->thread, NULL, deid_yet, info);
	i = 0;
	while (i++ < info->number)
		sem_wait(info->done);
	i = 0;
	while (i < info->number)
		kill(info->philos[i++].pid, SIGKILL);
	empty_trash(&heap);
}
