/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/13 14:42:16 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
*	@author @lh4j
 *
 *	@attention
 *		this error handling file is temporary
 *		im using it for handling parsing errors
 *		execution errors might be added later
 *		things can take an unexpeted round
 *
 *	@brief
 *		take this source code as a temporary
 *		error handling dummies to practice on
 */

#include <minishell.h>

/**
 * @todo add this commands list learing option for n == 1 !
 *		 parser.c:100 -> there was a shell.command = NULL instr
 * @param n
 * @param shell
 * @return
 */
int	raise_pipe_error(t_minishell *shell, int n)
{
	(void)shell;
	if (n == -1)
		ft_putstr_fd("syntax error near unexpected token `|\'\n", 2);
	if (n == 1)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	if (n == 1 || n == -1)
		g_ec = 2;
	return (1);
}

int	check_pipe_syntax(t_minishell *shell, t_tok token)
{
	if (token == PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		g_ec = 2;
		return (1);
	}
	if (shell->lexerlst == NULL)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}
