/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:07:31 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/15 03:30:27 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	run_so_bui(t_command *command, t_minishell *shell)
{
	char	**str;

	str = command->cmd_argv;
	if (str[0])
	{
		if (ft_strncmp(str[0], "export", ft_strlen(str[0])) == 0)
			export(str, shell->envlst, shell);
		else if (ft_strncmp(str[0], "unset", ft_strlen(str[0])) == 0)
			unset(str, shell);
		else if (ft_strncmp(str[0], "cd", ft_strlen(str[0])) == 0)
			cd(str, shell);
		else if (ft_strncmp(str[0], "exit", ft_strlen(str[0])) == 0)
			miniexit(str, shell);
	}
}

void	dup_in_out(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

char	*ft_getenv(char *str, t_list *list)
{
	char	*value;
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strncmp(((t_env *)tmp->content)->key, str, ft_strlen(str)) == 0)
		{
			value = ((t_env *)tmp->content)->val;
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	errors(char **str, t_minishell *shell, char **env)
{
	(void)shell;
	if (str[0][0] == '.' || str[0][0] == '/')
	{
		perror(str[0]);
		g_ec = 126;
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

void	pwd(t_minishell *shell)
{
	char	*pwd;
	t_list	*tmp;

	tmp = shell->envlst;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		while (tmp)
		{
			if (ft_strncmp(((t_env_var *)tmp->content)->key, "PWD", 3) == 0)
			{
				ft_putstr_fd(((t_env_var *)tmp->content)->val, 1);
				ft_putchar_fd('\n', 1);
				break ;
			}
			tmp = tmp->next;
		}
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}
