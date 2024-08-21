/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcollector.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/12 16:24:19 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GCOLLECTOR_H
# define GCOLLECTOR_H

# include <stddef.h>
# include <stdlib.h>

typedef struct s_gcollector
{
	void				*address;
	struct s_gcollector	*next;
}	t_gcollector;

/**
 * @brief fetches the last node !
 * @param gc yep the collector linked list
 * @return the last element NULL if gs is NULL
 */
t_gcollector	*get_last_gcn(t_gcollector *gc);

/**
 * @brief appends a node with addr as a value to the <collector>
 * @param collector collector my collector linked list
 * @param addr the address to add into the <collector>
 * @return an address to the new node NULL if the allocation failed !
 */
void			*gc_append(
					t_gcollector **collector,
					void *addr
					);

/**
 * @brief malloc with a mini garbage collector
 * @note  i didn't make my own heap allocator i just use malloc
 * @param collector my collector linked list
 * @param size bytes to be allocated !
 * @return an address for the allocated memory if fail's return's null !
 */
void			*gc_malloc(
					t_gcollector *collector,
					size_t size
					);

/**
 * @brief calloc with a mini garbage collector
 * @note  i didn't make my own heap allocator i just use calloc
 * @param collector my collector linked list
 * @param nmemb member's count !
 * @param size bytes to be allocated for each memb !
 * @return an address for the allocated memory if fail's return's null !
 */
void			*gc_calloc(
					t_gcollector *collector,
					size_t nmemb,
					size_t size
					);

/**
 * @brief free's up all allocated memory held by the <collector>
 * @param collector my collector linked list
 */
void			gc_free(t_gcollector **collector);

#endif