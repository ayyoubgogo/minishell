/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/12 16:24:10 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gcollector.h>

void	*gc_append(t_gcollector **collector, void *addr)
{
	t_gcollector	*node;
	t_gcollector	*last;

	node = (t_gcollector *)malloc(sizeof(t_gcollector));
	if (node == NULL)
		return (NULL);
	node->address = addr;
	node->next = NULL;
	if (*collector == NULL)
		*collector = node;
	last = get_last_gcn(*collector);
	last->next = node;
	return (node);
}
