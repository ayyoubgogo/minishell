/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+    +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:36:32 by agaougao            #+#   #+#           */
/*   Updated: 2024/05/24 15:36:32 by agaougao           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void split_env(t_env *env_node, char *str)
{
    char *val;
    int len;

    len = ft_strlen(str);
    val = ft_strnstr(str , "=", len);
    env_node->key = ft_substr(str , 0 , len - ft_strlen(val));
    env_node->val = ft_strdup(++val);
}

t_list *env_list(char **env)
{
    t_env *env_node;
    t_list *new;
    t_list *head;
    int i;

    head = NULL;
    i = 0;
    while(env[i])
    {
        env_node = malloc(sizeof(t_env));
        split_env(env_node,env[i]);
        new = ft_lstnew(env_node);
        ft_lstadd_back(&head,new);
        i++;     
    }
    return(head);
}
