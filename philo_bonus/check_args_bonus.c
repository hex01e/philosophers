/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:01:01 by houmanso          #+#    #+#             */
/*   Updated: 2023/05/20 20:22:15 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	valid(char *s, int flag)
{
	static int	i;
	static int	d;
	static int	n;
	char		c;

	c = (char) *s;
	if (flag)
	{
		i = 0;
		d = 0;
		n = 0;
	}
	if (c >= '0' && c <= '9' && !(d && n))
		return (d++, GOOD);
	else if ((c == '+' || c == '-') && !i
		&& *(s + 1) >= '0' && *(s + 1) <= '9')
		return (i++, GOOD);
	else if (c == ' ')
		return (n++, GOOD);
	return (BAD);
}

static int	check_av(char **av)
{
	int	i;
	int	j;
	int	f;

	i = 1;
	while (av[i])
	{
		j = 0;
		f = 1;
		while (av[i][j] == ' ')
			j++;
		if (!av[i][j])
			return (BAD);
		while (av[i][j])
		{
			if (!valid(&av[i][j], f))
				return (BAD);
			f = 0;
			j++;
		}
		i++;
	}
	return (GOOD);
}

t_info	*init_info(char **av, t_heap **heap)
{
	t_info	*info;
	int		i;

	i = 1;
	if (!check_av(av))
		return (NULL);
	info = ft_malloc(sizeof(t_info), heap);
	if (!info)
		return (NULL);
	while (av[i])
	{
		if (get_num(av[i++]) < 0)
			return (free(info), NULL);
	}
	info->number = get_num(av[1]);
	info->death_time = get_num(av[2]);
	info->eating_time = get_num(av[3]);
	info->sleeping_time = get_num(av[4]);
	info->times = -1;
	if (av[5])
		info->times = get_num(av[5]);
	return (info);
}
