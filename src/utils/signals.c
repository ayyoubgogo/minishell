/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/13 18:34:25 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	*sgl(int n)
{
	static int	n_;

	if (n != -1)
		n_ = n;
	return (&n_);
}

void	hd_handler(int sig)
{
	(void)sig;
	rl_clear_history();
	exit(6);
}

void	handler(int sig)
{
	(void)sig;
	if (*sgl(-1) == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_ec = 130;
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
}
