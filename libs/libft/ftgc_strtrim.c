/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgc_strtrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/12 23:50:09 by maomao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ftgc_strtrim(char const *s1, char const *set, t_gcollector *collector)
{
	char	*str;
	size_t	i;
	size_t	s;
	size_t	e;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	s = 0;
	while (s1[s] && ft_set(s1[s], set))
		s++;
	e = ft_strlen(s1);
	while (e > s && ft_set(s1[e - 1], set))
		e--;
	str = (char *)gc_malloc(collector, e - s + 1);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, e - s + 1);
	while (e > s)
		str[i++] = s1[s++];
	str[i] = 0;
	return (str);
}
