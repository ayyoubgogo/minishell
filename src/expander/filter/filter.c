/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 02:30:18 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/15 03:25:36 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_get_ac(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

static int	ft_fspaces(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

static char	**av_filter(t_command *command, t_gcollector *collector)
{
	char	**splitted_;
	char	**av;
	int		ac;
	int		i;
	int		j;

	av = NULL;
	ac = 0;
	i = 0;
	while (i < command->cmd_argc)
	{
		if (ft_fspaces(command->cmd_argv[i]) == 0)
			av = ftgc_tab_join(
					av, ac++, command->cmd_argv[i++], collector);
		else
		{
			splitted_ = ftgc_split(
					command->cmd_argv[i++], ' ', collector);
			j = 0;
			while (splitted_[j])
				av = ftgc_tab_join(
						av, ac++, splitted_[j++], collector);
		}
	}
	return (av);
}

void	filter_cmds(t_minishell *shell)
{
	t_command	*command;
	t_list		*tmp_node;

	tmp_node = shell->commands;
	while (tmp_node)
	{
		command = tmp_node->content;
		if (command->expanded == AYE_EXPAND)
		{
			command->cmd_argv = av_filter(
					command, &shell->collector);
			command->cmd_argc = ft_get_ac(command->cmd_argv);
		}
		tmp_node = tmp_node->next;
	}
}

void	filter_check(
	t_minishell *shell,
	char **ex_temp,
	char **av,
	int k
)
{
	t_command	*command;
	t_list		*commands;

	commands = shell->commands;
	while (commands)
	{
		command = commands->content;
		if (command->cmd_argv == av)
			break ;
		commands = commands->next;
	}
	*ex_temp = extend(shell, av[k]);
	if (shell->expand_code == AYE_EXPAND)
		command->expanded = AYE_EXPAND;
	av[k] = *ex_temp;
}
