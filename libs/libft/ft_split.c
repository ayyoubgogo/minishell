/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:36:35 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/12 23:29:48 by maomao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	words_count(char *str, char c)
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

size_t	words_len(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

void	free_array(int i, char **array)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}

char	**split_o(char const *s, char c, char **array, size_t word_count)
{
	size_t			i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < word_count)
	{
		while (s[j] && s[j] == c)
			j++;
		array[i] = ft_substr(s, j, words_len((char *)&s[j], c));
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

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	words;

	if (!s)
		return (NULL);
	words = words_count((char *)s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = split_o(s, c, array, words);
	return (array);
}
