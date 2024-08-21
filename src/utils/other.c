/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/15 12:21:21 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_builtin(char *str)
{
	if (str)
	{
		if (ft_strncmp(str, "echo", ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen("echo"))
			return (1);
		else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen("pwd"))
			return (3);
		else if (ft_strncmp(str, "export", ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen("export"))
			return (4);
		else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen("unset"))
			return (5);
		else if (ft_strncmp(str, "cd", ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen("cd"))
			return (2);
		else if (ft_strncmp(str, "env", ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen("env"))
			return (6);
		else if (ft_strncmp(str, "exit", ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen("exit"))
			return (7);
	}
	return (0);
}

int	check_red(t_minishell *shell, t_command *command)
{
	t_token	*redirection;
	t_list	*tmp;

	tmp = command->redirections;
	if (command->redirections == NULL)
		return (0);
	while (command->redirections)
	{
		redirection = (t_token *)(command->redirections->content);
		if (redirection->token == TRUNCATE)
			red_out(shell, command);
		else if (redirection->token == REDIRECT_INPUT)
			red_in(shell, command);
		else if (redirection->token == APPEND)
			append_red(shell, command);
		if (g_ec == 1)
			return (1);
		command->redirections = command->redirections->next;
	}
	command->redirections = tmp;
	return (0);
}
