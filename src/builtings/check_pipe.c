/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:23:17 by agaougao          #+#    #+#             */
/*   Updated: 2024/06/02 14:30:19 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"


int        check_pipe(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_strncmp(str[i], "|",1) == 0)
            return (1);
        i++;
    }
    return (0);
}