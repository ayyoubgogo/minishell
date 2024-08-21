/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/15 12:25:52 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_some(t_command *command, t_minishell *shell)
{
	t_token	*red;

	if (command->redirections)
	{
		if (check_red(shell, command) == 1)
			return (0);
		red = (t_token *)command->redirections->content;
		if (red->token == TRUNCATE || red->token == APPEND)
			dup_to_out(command);
	}
	return (1);
}

t_list	*sort_key(t_list *env)
{
	t_list	*tmp;
	t_list	*next;
	t_env	*env_tmp;

	tmp = env;
	while (tmp)
	{
		next = tmp->next;
		while (next)
		{
			if (ft_strncmp(((t_env *)tmp->content)->key,
					((t_env *)next->content)->key,
					ft_strlen(((t_env *)tmp->content)->key)) > 0)
			{
				env_tmp = (t_env *)tmp->content;
				tmp->content = next->content;
				next->content = env_tmp;
			}
			next = next->next;
		}
		tmp = tmp->next;
	}
	return (env);
}

void	declare(t_list *env)
{
	t_list	*tmp;

	tmp = sort_key(env);
	while (tmp)
	{
		printf("declare -x ");
		printf("%s", ((t_env *)tmp->content)->key);
		if (((t_env *)tmp->content)->val != NULL)
			printf("=%s", ((t_env *)tmp->content)->val);
		printf("\n");
		tmp = tmp->next;
	}
}

int	check_key(t_list *list, char *key, char *val)
{
	t_list	*tmp;

	(void)val;
	tmp = list;
	while (tmp)
	{
		if (ft_strncmp(((t_env *)tmp->content)->key, key, ft_strlen(key)) == 0)
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	here_doc_count(t_minishell *shell)
{
	t_list		*tmp;
	int			count;
	t_token		*red;
	t_command	*command;

	tmp = shell->commands;
	count = 0;
	while (shell->commands)
	{
		command = (t_command *)(shell->commands->content);
		tmp = command->redirections;
		while (command->redirections)
		{
			red = (t_token *)(command->redirections->content);
			if (red->token == HEREDOC)
				count++;
			command->redirections = command->redirections->next;
		}
		command->redirections = tmp;
		shell->commands = shell->commands->next;
	}
	return (count);
}
