/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgc_tab_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:33:14 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/15 00:58:59 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**************************************************************************
 * @brief make a copy of tab with str as last element (NULL ended array)
 * @param tab tab to copy from
 * @param size size of the tab
 * @param str string to append to the new tab
 * @param collector a garbage collector
 * @return a new tab with str in the end !
 **************************************************************************/
char	**ftgc_tab_join(
	char **tab,
	int size,
	char *str,
	t_gcollector *collector
)
{
	int		i;
	int		new_size;
	char	**new;

	if (str == NULL)
		return (tab);
	new_size = size + 2;
	new = (char **)gc_malloc(collector, sizeof(char *) * new_size);
	if (new == NULL)
		return (NULL);
	i = -1;
	while (++i < size)
		new[i] = ftgc_strdup(tab[i], collector);
	new[i++] = ftgc_strdup(str, collector);
	new[i] = NULL;
	return (new);
}
