/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:31:39 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/12 23:14:43 by maomao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str && len == 0)
		return (NULL);
	if (*str2 == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		if (str[i] == str2[0])
		{
			j = 0;
			while (str2[j] && str[i + j] && i + j < len && str[i
					+ j] == str2[j])
				j++;
			if (str2[j] == '\0')
				return ((char *)str + i);
		}
		i++;
	}
	return (0);
}
