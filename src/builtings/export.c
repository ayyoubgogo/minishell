/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:35:29 by agaougao          #+#    #+#             */
/*   Updated: 2024/05/26 10:36:11 by agaougao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
void declare(char **str, t_list *env)
{
    while(env)
    {
        if(((t_env *)env->content)->val)
        {
            printf("declare -x ");
            printf("%s",((t_env *)env->content)->key);
            printf("=%s", ((t_env *)env->content)->val);
            printf("\n");
        }
        env=env->next; 
    }

}

int check_key(t_list *list, char *key, char *val)
{
    t_list *tmp;

    tmp = list;
    while(tmp)
    {
        if(ft_strncmp(((t_env *)tmp->content)->key, key,ft_strlen(key)) == 0)
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

void add_val(t_list *list, char *key, char *val)
{
    t_list *tmp;
    char *env_var;
    char *value;

    tmp = list;
    while(tmp)
    {
        env_var = ((t_env *)tmp->content)->key;
        if(ft_strnstr(env_var, key, ft_strlen(key)) && ft_strlen(env_var) == ft_strlen(key))
        {
            value = ((t_env *)tmp->content)->val;
            ((t_env *)tmp->content)->val =  ft_strjoin(value,val);
        }
        tmp = tmp->next;
    }
}

void add_back_to_env(t_list *list, char *key, char *val)
{
    t_env *env;
    t_list *new;
    env = (t_env *)malloc(sizeof(t_env));
    env->key = ft_strdup(key);
    env->val = ft_strdup(val);
    new = ft_lstnew(env);
    ft_lstadd_back(&list,new);
}

void check_export(char **str,t_list *list , int i)
{
    t_list *new;
    char *env[2];
    t_env *envp;
    int len;
    char *tst;

    len = ft_strlen(str[i + 1]);
    tst = ft_strnstr(str[i + 1],"+=", len);
    if(tst)
    {
        env[0] = ft_substr(str[i + 1],0, len - ft_strlen(tst));
        env[1] = ft_strdup(tst + 2);
        if(check_key(list, env[0], env[1]) == 1)
            add_val(list, env[0], env[1]);
        else
            add_back_to_env(list, env[0], env[1]);
    }
    else
    {
        envp = (t_env *)malloc(sizeof(t_env));
        split_env(envp,str[i + 1]);
        new = ft_lstnew(envp);
        ft_lstadd_back(&list,new);
    }
}
void export(char **str,t_list *list , int  i)
{
        if(str[i + 1] == NULL)
            declare(str,list);
        else if(str[i + 1])
        {
           check_export(str,list , i);
        }
}
