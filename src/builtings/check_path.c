/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:22:00 by marvin            #+#    #+#             */
/*   Updated: 2024/08/09 21:03:52 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*check_valid_path(char **s, char **str)
{
	char	*path;
	int		i;
	char	*ptr;

	i = 0;
	while (str[i])
	{
		path = ft_strjoin(str[i], "/");
		ptr = ft_strjoin(path, s[0]);
		if (access(ptr, F_OK) == 0)
		{
			return (ptr);
		}
		free(ptr);
		free(path);
		i++;
	}
	return (NULL);
}

char	*check_exist_path(t_list *tmp)
{
	char	*value;
	char	*key;

	while (tmp)
	{
		key = ((t_env *)tmp->content)->key;
		if (ft_strncmp(key, "PATH", 4) == 0)
		{
			value = ((t_env *)tmp->content)->val;
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	**turn_env_tab(t_minishell *shell)
{
	t_list	*tmp;
	char	**env;
	char	*str;
	char	*ptr;
	int		i;

	i = 0;
	tmp = shell->envlst;
	env = malloc(sizeof(char *) * (ft_lstsize(shell->envlst) + 1));
	while (tmp)
	{
		if (((t_env *)tmp->content)->val)
		{
			str = ft_strjoin(((t_env *)tmp->content)->key, "=");
			ptr = ft_strjoin(str, ((t_env *)tmp->content)->val);
			env[i] = ft_strdup(ptr);
			free(ptr);
			free(str);
			i++;
		}
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

void	ft_free_tab(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	check_path(char *path, char **str, t_minishell *shell, char **env)
{
	(void)shell;
	if (access(path, X_OK) == 0)
	{
		if (execve(path, str, env))
		{
			perror("execve");
			ft_free_tab(env);
		}
	}
}
