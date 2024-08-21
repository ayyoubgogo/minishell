/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:32:00 by agaougao          #+#    #+#             */
/*   Updated: 2024/04/23 17:59:31 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_nsize(int n)
{
	int	size;

	size = 1;
	if (n < 0)
	{
		size++;
		n = -n;
	}
	if (!n)
		return (size);
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size - 1);
}

static void	init_nb(unsigned int *nb, int n, char *buffer)
{
	if (n < 0)
	{
		buffer[0] = '-';
		*nb = -n;
	}
	else
		*nb = n;
}

char	*ftgc_itoa(int n, t_gcollector *collector)
{
	unsigned int	nb;
	int				size;
	char			*buffer;

	size = get_nsize(n);
	buffer = (char *)gc_malloc(collector, size + 1);
	if (!buffer)
		return (NULL);
	buffer[size] = 0;
	if (!n)
	{
		buffer[0] = '0';
		return (buffer);
	}
	init_nb(&nb, n, buffer);
	while (--size)
	{
		buffer[size] = nb % 10 + '0';
		nb /= 10;
	}
	if (nb)
		buffer[size] = nb % 10 + '0';
	return (buffer);
}
