/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:07:24 by houmanso          #+#    #+#             */
/*   Updated: 2023/05/19 13:08:40 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <semaphore.h>

# define BAD 0
# define GOOD 1
# define DONE -2

typedef struct s_philo	t_philo;
typedef struct s_info	t_info;
typedef struct s_heap	t_heap;

struct s_info
{
	sem_t		*forks;
	sem_t		*print;
	sem_t		*death;
	sem_t		*done;
	t_philo		*philos;
	t_heap		**heap;
	int			times;
	long		begin;
	int			number;
	int			death_time;
	pthread_t	thread;
	int			eating_time;
	int			sleeping_time;
};

struct s_philo
{
	int			id;
	sem_t		*lock;
	pid_t		pid;
	t_info		*info;
	char		*name;
	sem_t		*last_sem;
	long		last_eat;
	pthread_t	thread;
};

struct s_heap
{
	void	*addr;
	t_heap	*next;
};

long	get_num(char *s);
long	get_time(t_info *info);

t_info	*init_info(char **av, t_heap **heap);

void	*status_synch(void *p);
void	empty_trash(t_heap **heap);
void	print(t_philo *this, char *msg);
void	error(char *msg, t_heap **heap);
void	activity(t_philo *this, t_info *info);
void	lets_exit(t_info *info, t_heap **heap);
void	*ft_malloc(size_t size, t_heap **heap);
void	init_semphs(t_info *info, t_heap **heap);
void	nap(long time, t_info *info, t_philo *this);
void	gen_name(t_philo *this, char *s, t_heap **heap);

#endif // PHILO_BONUS_H
