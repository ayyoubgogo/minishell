/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:04 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/12 14:30:58 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_quote	is_quoted(const char *delimiter)
{
	int	e;

	e = ft_strlen(delimiter) - 1;
	if (delimiter[0] == SINGLE_QUOTE && delimiter[e] == SINGLE_QUOTE)
		return (SINGLE_QUOTE);
	else if (delimiter[0] == DOUBLE_QUOTE && delimiter[e] == DOUBLE_QUOTE)
		return (DOUBLE_QUOTE);
	return (-1);
}

static int	heredoc_checks(
	t_token *redir,
	t_minishell *shell,
	char **expanded_promp,
	char *promp
)
{
	char	*cmp_word;

	cmp_word = promp;
	if (ft_strlen(promp) < ft_strlen(redir->word))
		cmp_word = redir->word;
	if (ft_strncmp(promp, redir->word, ft_strlen(cmp_word)) == 0)
	{
		free(promp);
		return (1);
	}
	if (shell->hd_expand == 0)
		*expanded_promp = promp;
	else
		*expanded_promp = expand_string(shell, promp);
	return (0);
}

static void	trigger_here_doc(
	t_minishell *shell,
	t_token *redir,
	int fd,
	int expand
)
{
	char	*expanded_promp;
	char	*promp;

	expanded_promp = NULL;
	shell->hd_expand = expand;
	while (1)
	{
		promp = readline("> ");
		if (promp == NULL)
			break ;
		if (promp[0] != 0)
		{
			if (heredoc_checks(
					redir, shell, &expanded_promp, promp) == 0)
				write(fd, expanded_promp, ft_strlen(expanded_promp));
			else
				break ;
		}
		write(fd, "\n", 1);
	}
}

void	child_here_doc(t_minishell *shell, t_command *command)
{
	t_token	*redir;
	int		fd;
	int		expand;

	redir = (t_token *)(command->redirections->content);
	signal(SIGINT, &hd_handler);
	fd = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd != -1)
	{
		if (redir->token == HEREDOC)
		{
			expand = (int)is_quoted(redir->word) == -1;
			if ((int)is_quoted(redir->word) != -1)
				redir->word = delete_quotes(redir->word,
						is_quoted(redir->word));
			trigger_here_doc(shell, redir, fd, expand);
		}
	}
}

int	here_doc(t_minishell *shell, t_command *command)
{
	int	pid;
	int	fd1;
	int	status;

	*sgl(-1) = 1;
	pid = fork();
	if (pid == 0)
	{
		child_here_doc(shell, command);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == 6)
		{
			g_ec = 130;
			return (2);
		}
		fd1 = open("/tmp/here_doc", O_RDWR);
		command->redirections->fd = fd1;
	}
	return (0);
}
