/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/12 14:53:47 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exist_path(char *ptr, char **str, t_minishell *shell, char **env)
{
	char	**split;
	char	*path;

	split = ft_split(ptr, ':');
	path = check_valid_path(str, split);
	if (path != NULL)
		check_path(path, str, shell, env);
	else
	{
		if (str[0][0] == '.' || str[0][0] == '/')
		{
			ft_putstr_fd(str[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_ec = 127;
			ft_free_tab(env);
		}
		else
		{
			ft_putstr_fd(str[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			g_ec = 127;
			ft_free_tab(env);
		}
	}
	ft_free_tab(split);
}

static void	fsub_check(t_minishell *shell, char **str, char **env)
{
	if (access(str[0], X_OK) == 0)
	{
		if (execve(str[0], str, env))
		{
			if (str[0][0] == '.' || str[0][0] == '/')
			{
				ft_putstr_fd(str[0], 2);
				ft_putstr_fd(": Is a directory\n", 2);
				g_ec = 126;
				ft_free_tab(env);
			}
			else
			{
				ft_putstr_fd(" command not found\n", 2);
				g_ec = 127;
				ft_free_tab(env);
			}
		}
	}
	else
		errors(str, shell, env);
}

static void	ssub_check(t_minishell *shell, t_list *tmp, char ***data, char *ptr)
{
	ptr = check_exist_path(tmp);
	if (ptr == NULL)
	{
		ft_putstr_fd(data[0][0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_ec = 127;
		ft_free_tab(data[1]);
	}
	else
		exist_path(ptr, data[0], shell, data[1]);
}

static int	skip_empty_args(char **argv, int argc)
{
	int	i;

	i = 0;
	if (argv[i] == NULL)
		return (-1);
	while (i < argc && argv[i][0] == '\0')
		i++;
	if (i > argc - 1)
		return (-1);
	return (i);
}

void	check(t_minishell *shell, t_command *command)
{
	t_list	*tmp;
	char	*ptr;
	char	**str;
	char	**env;
	char	**data[2];

	ptr = NULL;
	tmp = shell->envlst;
	str = command->cmd_argv;
	if (skip_empty_args(str, command->cmd_argc) != -1)
		str = &str[skip_empty_args(str, command->cmd_argc)];
	else
		return ;
	if (check_builtin(str[0]) != 0)
		builting(str, shell);
	else
	{
		env = turn_env_tab(shell);
		data[0] = str;
		data[1] = env;
		if (access(str[0], F_OK) == 0)
			fsub_check(shell, str, env);
		else
			ssub_check(shell, tmp, data, ptr);
	}
}
