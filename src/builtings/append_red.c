/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:45:15 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/15 12:16:00 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	append_red(t_minishell *shell, t_command *command)
{
	t_token	*redirection;
	int		fd;

	(void)shell;
	redirection = ((t_token *)command->redirections->content);
	fd = open(redirection->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd != -1)
		command->redirections->fd = fd;
	else
	{
		perror(redirection->word);
		g_ec = 1;
	}
}
