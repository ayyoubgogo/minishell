/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:17:03 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/15 03:31:23 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	change_pwd(t_minishell *shell)
{
	t_list	*env;
	char	*pwd;

	env = shell->envlst;
	while (env)
	{
		if (ft_strncmp(((t_env *)env->content)->key, "PWD", 3) == 0)
		{
			free(((t_env *)env->content)->val);
			pwd = getcwd(NULL, 0);
			((t_env *)env->content)->val = ft_strdup(pwd);
			free(pwd);
		}
		if (ft_strncmp(((t_env *)env->content)->key, "OLDPWD", 6) == 0)
		{
			free(((t_env *)env->content)->val);
			((t_env *)env->content)->val = ft_strdup(shell->oldpwd);
		}
		env = env->next;
	}
}

void	cd_hel(t_minishell *shell, int status)
{
	char	*home;

	home = ft_getenv("HOME", shell->envlst);
	if (home == NULL)
	{
		ft_putstr_fd("cd: $HOME not set\n", 2);
		g_ec = 1;
	}
	else
	{
		status = chdir(home);
		if (status != 0)
		{
			ft_putstr_fd("cd: no such file or directory: \n", 2);
			g_ec = 1;
		}
		else
		{
			change_pwd(shell);
		}
	}
}

void	change_dir(t_minishell *shell, int status, char *path)
{
	status = chdir(path);
	if (status != 0)
	{
		ft_putstr_fd("cd", 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		g_ec = 1;
	}
	else
	{
		change_pwd(shell);
	}
}

void	cd_c(char *path, t_minishell *shell)
{
	char	*oldpwd;
	int		status;

	status = 0;
	oldpwd = getcwd(NULL, 0);
	shell->oldpwd = ft_strdup(oldpwd);
	free(oldpwd);
	if (path == NULL)
		cd_hel(shell, status);
	else
	{
		change_dir(shell, status, path);
	}
}

void	cd(char **str, t_minishell *shell)
{
	char	*path;

	path = str[1];
	if (count_str(str) >= 3
		&& ((t_command *)shell->commands->content)->redirections == NULL)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		g_ec = 1;
	}
	else
	{
		if (shell->oldpwd)
		{
			free(shell->oldpwd);
		}
		cd_c(path, shell);
	}
}
