/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/10 13:36:01 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gcollector.h>

void	*gc_malloc(t_gcollector *collector, size_t size)
{
	void	*addr;

	addr = malloc(size);
	if (addr == NULL)
		return (NULL);
	gc_append(&collector, addr);
	return (addr);
}
