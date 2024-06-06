/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:03:01 by agaougao          #+#    #+#             */
/*   Updated: 2024/04/23 18:03:03 by agaougao         ###   ########.fr       */
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

char	*ft_strtrim(char const *s1, char const *set)
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
	str = (char *)malloc(e - s + 1);
	if (!str)
		return (NULL);
	while (e > s)
	{
		str[i] = s1[s];
		i++;
		s++;
	}
	str[i] = 0;
	return (str);
}
