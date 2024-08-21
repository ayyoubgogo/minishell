/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/12 16:24:07 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gcollector.h>

void	gc_free(t_gcollector **collector)
{
	t_gcollector	*tmp;
	unsigned int	i;

	i = 0;
	while (*collector)
	{
		tmp = (*collector)->next;
		free((*collector)->address);
		if (i)
			free(*collector);
		i++;
		*collector = tmp;
	}
}
