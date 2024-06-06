/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:36:06 by agaougao          #+#    #+#             */
/*   Updated: 2024/04/23 18:00:32 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	if (!n)
		return (s1);
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 <= s2)
		ft_memcpy(s1, s2, n);
	else
	{
		while (--n)
			*(char *)(s1 + n) = *(char *)(s2 + n);
		*(char *)(s1) = *(char *)(s2);
	}
	return (s1);
}
