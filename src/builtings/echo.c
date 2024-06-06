/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:57:23 by agaougao          #+#    #+#             */
/*   Updated: 2024/05/30 16:27:20 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo(char **str , int j)
{
    int  i;

    i = 1;
    if(str[j + 1] == NULL)
        printf("\n");
    else if(ft_strncmp(str[j + 1], "-n",2) == 0)
    {
        while(str[j + i])
        {
            if(ft_strncmp(str[j + i], "-n",2) != 0)
                break;
            else
                i++;
        }
        if(str[j + i] == NULL)
            printf("");
        else
            printf("%s",str[j + i]);
    }
    else
        printf("%s\n",str[j + i]);
}
