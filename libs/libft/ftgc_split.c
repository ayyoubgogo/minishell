/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgc_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maomao <hmouhib@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:29:52 by maomao            #+#    #+#             */
/*   Updated: 2024/08/12 22:45:53 by maomao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	words_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
		else if (str[i] == c)
			i++;
	}
	return (count);
}

static size_t	words_len(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

/**
	@todo figure out a way to use gc_free instead !
*/
static void	free_array(int i, char **array)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}

static char	**split_o(
	char const *s,
	char c,
	char **array,
	t_gcollector *collector
)
{
	size_t			i;
	size_t			word_count;
	unsigned int	j;

	i = 0;
	j = 0;
	word_count = words_count((char *)s, c);
	while (i < word_count)
	{
		while (s[j] && s[j] == c)
			j++;
		array[i] = ftgc_substr(s, j, words_len((char *)&s[j], c), collector);
		if (!array[i])
		{
			free_array(i, array);
			return (NULL);
		}
		while (s[j] && s[j] != c)
			j++;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ftgc_split(char const *s, char c, t_gcollector *collector)
{
	char	**array;
	size_t	words;

	if (!s)
		return (NULL);
	words = words_count((char *)s, c);
	array = (char **)gc_malloc(collector, sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = split_o(s, c, array, collector);
	return (array);
}
