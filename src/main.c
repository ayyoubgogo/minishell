/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/15 19:49:26 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_ec;

int	main(int argc, char **argv, char **envp)
{
	t_minishell		shell;
	t_gcollector	*collector;

	(void)argc;
	(void)argv;
	collector = &(shell.collector);
	init_minishell(&shell, envp);
	sgl(0);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	shell_loop(&shell, &collector, envp);
}
