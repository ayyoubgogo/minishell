/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:32:39 by agaougao          #+#    #+#             */
/*   Updated: 2024/06/02 16:44:25 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list *turn_to_list(c_cmd command)
{
    t_tmp *tmp;
    t_list *new;
    t_list *head;
    int i;

    head = NULL;
    i = 0;
    while(command.cmd[i])
    {
        tmp = malloc(sizeof(t_tmp));
        tmp->cmd = command.cmd;
        new = ft_lstnew(tmp);
        ft_lstadd_back(&head , new);
        i++;
    }
    return(head);
}
void run_builting(char **str,t_minishell *shell, int i)
{
    printf("%d\n",i);
    if(ft_strncmp(str[i],"pwd", 3) == 0)
        pwd(str);
    if(ft_strncmp(str[i],"exit", 4) == 0)
        miniexit(str);
    if(ft_strncmp(str[i],"cd", 2) == 0)
        cd(str,i);
    if(ft_strncmp(str[i],"echo", 4) == 0)
        echo(str,i);
    if(ft_strncmp(str[i], "env", 3) == 0)
        mini_env(shell->env);
    if(ft_strncmp(str[i],"export", 5) == 0)
        export(str,shell->env,i);
    if(ft_strncmp(str[i],"unset", 3) == 0)
        unset(str, shell,i);
}

void pipex(c_cmd cmd , t_minishell *shell)
{
    t_list *list;
    char **str;
    c_cmd *command;
    int i;

    list = turn_to_list(cmd);
    i = 0;
    while(list)
    {
        str = ((t_tmp *)list->content)->cmd;
        if(check_builtin(str[i]))
            run_builting(str ,shell, i);
        // else if()
        list = list->next;
        i++;
    }
}
