/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_last.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/12 16:24:03 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gcollector.h>

t_gcollector	*get_last_gcn(t_gcollector *gc)
{
	t_gcollector	*last;

	last = gc;
	while (last->next)
		last = last->next;
	return (last);
}
