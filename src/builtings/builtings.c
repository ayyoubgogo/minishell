/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:59:06 by agaougao          #+#    #+#             */
/*   Updated: 2024/05/30 16:28:04 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void builting(c_cmd command , t_minishell *shell)
{
    t_list *list;
    
    if(ft_strncmp(command.cmd[0],"pwd", 3) == 0)
        pwd(command.cmd);
    if(ft_strncmp(command.cmd[0] , "exit", 4) == 0)
        miniexit(command.cmd);
    if(ft_strncmp(command.cmd[0] ,"cd",2) == 0)
        cd(command.cmd);
    if(ft_strncmp(command.cmd[0], "echo",4) == 0)
        echo(command.cmd);
    if(ft_strncmp(command.cmd[0], "env", 3) == 0)
        mini_env(shell->env);
    if(ft_strncmp(command.cmd[0] , "export", 5) == 0)
        export(command.cmd,shell->env);
    if(ft_strncmp(command.cmd[0] , "unset", 5) == 0)
        unset(command.cmd, shell);
    
}
