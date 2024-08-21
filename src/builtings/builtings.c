/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:59:06 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/15 12:03:58 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_so_bui(t_command *command)
{
	char	**str;

	str = command->cmd_argv;
	if (str[0])
	{
		if (ft_strncmp(str[0], "export", ft_strlen(str[0])) == 0
			&& ft_strlen(str[0]) == strlen("export"))
			return (1);
		else if (ft_strncmp(str[0], "unset", ft_strlen(str[0])) == 0
			&& ft_strlen(str[0]) == strlen("unset"))
			return (1);
		else if (ft_strncmp(str[0], "cd", ft_strlen(str[0])) == 0
			&& ft_strlen(str[0]) == strlen("cd"))
			return (1);
		else if (ft_strncmp(str[0], "exit", ft_strlen(str[0])) == 0
			&& ft_strlen(str[0]) == strlen("exit"))
			return (1);
	}
	return (0);
}

void	add_to_list(t_env_var *envp, t_list *new, char *str, t_list *list)
{
	envp = (t_env_var *)malloc(sizeof(t_env_var));
	split_env(envp, str);
	new = ft_lstnew(envp);
	ft_lstadd_back(&list, new);
}

void	double_quote_expo(char *str, t_list *list, int len)
{
	char		*env[2];
	t_list		*new;
	t_env_var	*envp;

	env[0] = ft_substr(str, 0, len - ft_strlen(ft_strnstr(str, "=", len)));
	env[1] = ft_strdup(ft_strnstr(str, "=", len) + 1);
	new = NULL;
	envp = NULL;
	if (check_char(env[0]) == 0)
	{
		ft_putstr_fd(env[0], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_ec = 1;
	}
	else
	{
		if (check_key(list, env[0], env[1]) == 1)
			change_val(list, env[0], env[1]);
		else if (env[1][0] == '\0')
			add_back_to_env(list, env[0], "\0");
		else
			add_to_list(envp, new, str, list);
	}
	free(env[0]);
	free(env[1]);
}

void	builting(char **str, t_minishell *shell)
{
	if (ft_strncmp(str[0], "pwd", ft_strlen(str[0])) == 0
		&& ft_strlen(str[0]) == ft_strlen("pwd"))
		pwd(shell);
	if (ft_strncmp(str[0], "exit", ft_strlen(str[0])) == 0
		&& ft_strlen(str[0]) == ft_strlen("exit"))
		miniexit(str, shell);
	if (ft_strncmp(str[0], "cd", ft_strlen(str[0])) == 0
		&& ft_strlen(str[0]) == ft_strlen("cd"))
		cd(str, shell);
	if (ft_strncmp(str[0], "echo", ft_strlen(str[0])) == 0
		&& ft_strlen(str[0]) == ft_strlen("echo"))
		echo(str, shell);
	if (ft_strncmp(str[0], "env", ft_strlen(str[0])) == 0
		&& ft_strlen(str[0]) == ft_strlen("env"))
		mini_env(shell->envlst, shell);
	if (ft_strncmp(str[0], "export", ft_strlen(str[0])) == 0
		&& ft_strlen(str[0]) == ft_strlen("export"))
		export(str, shell->envlst, shell);
	if (ft_strncmp(str[0], "unset", ft_strlen(str[0])) == 0
		&& ft_strlen(str[0]) == ft_strlen("unset"))
		unset(str, shell);
}
