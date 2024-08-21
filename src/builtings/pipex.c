/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:32:39 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/15 20:54:04 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sq_handler(int sig)
{
	(void)sig;
	printf(" quit (core dumped)\n");
}

void	dup_to_out(t_command *command)
{
	dup2(command->redirections->fd, 1);
	close(command->redirections->fd);
}

void	dup_red(t_command *command)
{
	t_token	*red;

	if (command->redirections)
	{
		while (command->redirections)
		{
			red = (t_token *)command->redirections->content;
			if (red->token == REDIRECT_INPUT || red->token == HEREDOC)
			{
				if (access(red->word, F_OK) == -1
					&& red->token == REDIRECT_INPUT)
					exit(1);
				else
				{
					dup2(command->redirections->fd, 0);
					close(command->redirections->fd);
				}
			}
			else if (red->token == TRUNCATE || red->token == APPEND)
				dup_to_out(command);
			command->redirections = command->redirections->next;
		}
	}
}

void	pipe_hel(t_command *command, t_minishell *shell)
{
	dup_red(command);
	check(shell, command);
	exit(g_ec);
}

void	pipex(t_minishell *shell, t_command *command, t_command *nex_command)
{
	int	fd[2];

	pipe(fd);
	shell->commands->pid = fork();
	sgl(shell->commands->pid);
	signal(SIGQUIT, &sq_handler);
	if (shell->commands->pid == 0)
	{
		if (check_red(shell, command) == 1)
			exit(g_ec);
		if (nex_command)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
		}
		pipe_hel(command, shell);
	}
	if (nex_command)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
	}
}
