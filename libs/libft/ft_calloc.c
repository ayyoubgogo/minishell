/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:34:26 by agaougao          #+#    #+#             */
/*   Updated: 2023/11/24 11:59:45 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t s, size_t size)
{
	void	*ptr;

	if (size && s * size > (size_t)-1)
		return (NULL);
	ptr = (void *)malloc(s * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, s * size);
	return (ptr);
}
