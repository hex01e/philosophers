/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:31:47 by houmanso          #+#    #+#             */
/*   Updated: 2023/05/23 15:31:47 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	count_digits(long n)
{
	int	size;

	size = 0;
	if (n <= 0)
	{
		size += 1;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*ft_itoa(int n, t_heap **heap)
{
	long	nbr;
	int		size;
	char	*str;

	nbr = n;
	size = count_digits(nbr);
	str = ft_malloc(sizeof(char) * (size + 1), heap);
	if (!str)
		return (NULL);
	str[size--] = '\0';
	if (n == 0)
		str[size] = '0';
	if (n < 0)
	{
		nbr *= -1;
		str[0] = '-';
	}
	while (nbr > 0)
	{
		str[size--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}

void	gen_name(t_philo *this, char *s, t_heap **heap)
{
	char	*nbr;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nbr = ft_itoa(this->id, heap);
	len = ft_strlen(nbr) + ft_strlen(s) + 1;
	this->name = ft_malloc(sizeof(char) * len, heap);
	if (!this->name)
		return ;
	while (s[i])
	{
		this->name[i] = s[i];
		i++;
	}
	while (nbr[j])
		this->name[i++] = nbr[j++];
	this->name[len] = '\0';
}
