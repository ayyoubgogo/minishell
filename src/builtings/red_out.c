/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:07:31 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/15 12:15:48 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	red_out(t_minishell *shell, t_command *cmd)
{
	int		file;
	char	*file_name;

	(void)shell;
	file_name = ((t_token *)cmd->redirections->content)->word;
	file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file != -1)
		cmd->redirections->fd = file;
	else
	{
		perror(file_name);
		g_ec = 1;
	}
}
