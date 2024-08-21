/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgc_calloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maomao <hmouhib@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:29:52 by maomao            #+#    #+#             */
/*   Updated: 2024/08/12 23:38:36 by maomao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ftgc_calloc(size_t s, size_t size, t_gcollector *collector)
{
	void	*ptr;

	if (size && s * size > (size_t)-1)
		return (NULL);
	ptr = (void *)gc_malloc(collector, s * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, s * size);
	return (ptr);
}
