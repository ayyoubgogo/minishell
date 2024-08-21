/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgc_substr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maomao <hmouhib@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:29:52 by maomao            #+#    #+#             */
/*   Updated: 2024/08/12 22:45:53 by maomao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ftgc_substr(char const *s, unsigned int start, size_t len,
		t_gcollector *collector)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (0);
	str = (char *)gc_malloc(collector, (len + 1));
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}
