/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/14 19:06:31 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	local_parser(t_minishell *shell)
{
	int			qcheck;

	qcheck = check_quotes(shell->input);
	if (!qcheck)
		tokenize_input(shell);
	else
	{
		ft_putstr_fd("syntax error: unclosed quote !\n", 2);
		g_ec = 2;
		return (1);
	}
	if (shell->lexerlst)
	{
		if (parser(shell) != 0)
			return (1);
		expander(shell);
		filter_cmds(shell);
	}
	return (0);
}

static int	verify_input(t_minishell *shell)
{
	if (shell->input == NULL)
	{
		if (shell->oldpwd)
			free(shell->oldpwd);
		printf("exit\n");
		return (1);
	}
	return (0);
}

void	init_minishell(t_minishell *shell_struct, char **envp)
{
	ft_bzero(
		&(shell_struct->collector),
		sizeof(t_gcollector)
		);
	shell_struct->hd_expand = 0;
	shell_struct->exit_status = 0;
	shell_struct->envlst = init_env(envp);
	shell_struct->lexerlst = NULL;
	shell_struct->input = NULL;
	shell_struct->commands = NULL;
	shell_struct->pwd = NULL;
	shell_struct->oldpwd = NULL;
}

void	shell_loop(
	t_minishell *shell,
	t_gcollector **collector,
	char **envp
)
{
	(void)envp;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		shell->lexerlst = NULL;
		shell->input = readline(PROMPT);
		if (verify_input(shell))
			break ;
		if (local_parser(shell) == 0 && shell->commands != NULL)
		{
			g_ec = 0;
			check_pipe(shell);
			sgl(0);
			signal(SIGQUIT, handler);
			shell->commands = NULL;
		}
		if (shell->input[0] != '\0')
			add_history(shell->input);
	}
	gc_free(collector);
	clear_envlst(&shell->envlst, env_del);
}
