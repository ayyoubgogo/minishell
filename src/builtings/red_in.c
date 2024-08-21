/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:47:34 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/15 12:15:28 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	red_in(t_minishell *shell, t_command *command)
{
	char	*file_name;
	int		file;

	(void)shell;
	file_name = ((t_token *)command->redirections->content)->word;
	if (access(file_name, F_OK) == -1)
	{
		perror(file_name);
		g_ec = 1;
	}
	else
	{
		file = open(file_name, O_RDONLY);
		if (file != -1)
			command->redirections->fd = file;
		else
		{
			perror(file_name);
			g_ec = 1;
		}
	}
}
