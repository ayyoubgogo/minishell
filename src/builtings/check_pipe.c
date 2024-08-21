/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:23:17 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/15 20:51:27 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	run_her_doc(t_minishell *shell)
{
	t_command	*command;
	t_token		*red;
	t_list		*tmp;
	int			status;

	while (shell->commands)
	{
		command = (t_command *)(shell->commands->content);
		tmp = command->redirections;
		while (command->redirections)
		{
			red = (t_token *)(command->redirections->content);
			if (red->token == HEREDOC)
			{
				status = here_doc(shell, command);
				if (status == 2)
					return (1);
			}
			command->redirections = command->redirections->next;
		}
		command->redirections = tmp;
		shell->commands = shell->commands->next;
	}
	return (0);
}

int	run_pipe(t_minishell *shell)
{
	t_command	*command;
	t_command	*nex_command;

	while (shell->commands)
	{
		nex_command = NULL;
		command = (t_command *)(shell->commands->content);
		if (shell->commands->next)
			nex_command = (t_command *)(shell->commands->next->content);
		if (check_so_bui(command) != 0 && nex_command == NULL)
		{
			if (check_some(command, shell) == 0)
				return (1);
			run_so_bui(command, shell);
			return (1);
		}
		else
			pipex(shell, command, nex_command);
		shell->commands = shell->commands->next;
	}
	return (0);
}

int	nor_dup(t_minishell *shell, int out, int in)
{
	int	s;

	s = run_pipe(shell);
	if (s == 1)
	{
		dup2(out, 1);
		dup2(in, 0);
		return (1);
	}
	return (0);
}

void	parent_wait(t_minishell *shell)
{
	int	status;

	while (shell->commands)
	{
		waitpid(shell->commands->pid, &status, 0);
		if (WIFEXITED(status))
			g_ec = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_ec = WTERMSIG(status) + 128;
		shell->commands = shell->commands->next;
	}
}

int	check_pipe(t_minishell *shell)
{
	t_list	*tmp;
	int		out;
	int		in;

	out = dup(1);
	in = dup(0);
	tmp = shell->commands;
	if (here_doc_count(shell) > 16)
	{
		dup_in_out(in, out);
		ft_putstr_fd(" maximum here-document count exceeded\n", 2);
		return (2);
	}
	shell->commands = tmp;
	if (run_her_doc(shell) == 1)
	{
		dup_in_out(in, out);
		return (0);
	}
	shell->commands = tmp;
	if (nor_dup(shell, out, in) == 1)
		return (0);
	shell->commands = tmp;
	dup_in_out(in, out);
	return (parent_wait(shell), 0);
}
