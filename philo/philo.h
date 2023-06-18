/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:52:11 by houmanso          #+#    #+#             */
/*   Updated: 2023/05/14 16:24:15 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

# define BAD 0
# define GOOD 1
# define DONE -2

typedef struct s_philo	t_philo;
typedef struct s_info	t_info;
typedef struct s_heap	t_heap;

struct s_info
{
	int				times;
	long			begin;
	int				number;
	int				death_time;
	int				eating_time;
	int				sleeping_time;
	pthread_mutex_t	print;
};

struct s_philo
{
	int				id;
	long			last_eat;
	long			done;
	t_philo			*next;
	t_philo			*last;
	t_info			*info;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	time;
};

struct s_heap
{
	void	*addr;
	t_heap	*next;
};

long	get_num(char *s);
long	get_time(t_info *info);

t_info	*init_info(char **av, t_heap **heap);

int		done_yet(t_philo *p);
int		is_died(t_philo *philo, t_info *info);
int		setup_philos(t_philo **philo, t_info *info, t_heap **heap);

void	*activity(void *p);
void	empty_trash(t_heap **heap);
void	nap(long time, t_info *info, t_philo *this);
void	*_malloc(size_t size, t_heap **heap);
void	print(t_philo *this, char *msg, int flag);

#endif
