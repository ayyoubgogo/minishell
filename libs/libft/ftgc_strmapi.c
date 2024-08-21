/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgc_strmapi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maomao <hmouhib@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:29:52 by maomao            #+#    #+#             */
/*   Updated: 2024/08/12 22:45:53 by maomao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ftgc_strmapi(char const *s, char (*f)(unsigned int, char),
		t_gcollector *collector)
{
	unsigned int	i;
	size_t			len;
	char			*string;

	len = ft_strlen(s) + 1;
	string = (char *)gc_malloc(collector, len);
	if (!string)
		return (NULL);
	i = 0;
	while (s[i])
	{
		string[i] = f(i, s[i]);
		i++;
	}
	string[i] = 0;
	return (string);
}
