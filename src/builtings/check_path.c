/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:22:00 by marvin            #+#    #+#             */
/*   Updated: 2024/05/23 13:22:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *check_valid_path(c_cmd cmd , char **str)
{
    char *path;
    int i;
    char *ptr;

    i = 0;
    while(str[i])
    {
        path = ft_strjoin(str[i], "/");
        ptr = ft_strjoin(path, cmd.cmd[0]);
        if(access(ptr, F_OK) == 0)
        {
            return ptr;
        }
        i++;
    }
    return NULL;
}

char  *check_exist_path(t_list *tmp)
{
    char *value;
    char *key;
    
    while (tmp)
    {
        key = ((t_env *)tmp->content)->key;
        if(ft_strncmp(key , "PATH", 4) == 0)
        {
            value = ((t_env *)tmp->content)->val;
            return (value);
        }
        tmp = tmp->next;
    }
    return (NULL);
}
char **turn_env_tab(t_minishell *shell)
{
    t_list *tmp;
    char **env;
    int i;
    i = 0;
    tmp = shell->env;
    env = malloc(sizeof(char *) * (ft_lstsize(shell->env) + 1));
    while (tmp)
    {
        env[i] = ft_strdup(((t_env *)tmp->content)->val);
        i++;
        tmp = tmp->next;
    }
    env[i] = NULL;
    return env;
}

void check_path(char *path,c_cmd cmd , t_minishell *shell)
{
    char **env;
    pid_t pid;
    env = turn_env_tab(shell);
    if(access(path, X_OK) == 0)
    {
        pid = fork();
        if(pid == 0)
            execve(path, cmd.cmd,env);
        waitpid(pid, NULL, 0);
    }
}
