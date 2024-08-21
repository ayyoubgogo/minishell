/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/09 21:00:52 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+    +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:36:32 by agaougao            #+#   #+#           */
/*   Updated: 2024/05/24 15:36:32 by agaougao           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	split_env(t_env_var *env_node, char *str)
{
	char	*val;
	int		len;

	len = ft_strlen(str);
	val = ft_strnstr(str, "=", len);
	env_node->key = ft_substr(str, 0, len - ft_strlen(val));
	env_node->val = ft_strdup(++val);
}

void	add_path_to_env(t_env_var *env_node)
{
	char	*path;
	char	*path1;
	char	*join;

	path = "/nfs/homes/agaougao/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:";
	path1 = "/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
	join = ft_strjoin(path, path1);
	env_node->key = ft_strdup("PATH");
	env_node->val = ft_strdup(join);
	free(join);
}

t_list	*env_list(char **env)
{
	t_env_var	*env_node;
	t_list		*new;
	t_list		*head;
	int			i;

	head = NULL;
	i = 0;
	if (env[0] == NULL)
	{
		env_node = malloc(sizeof(t_env_var));
		add_path_to_env(env_node);
		new = ft_lstnew(env_node);
		ft_lstadd_back(&head, new);
	}
	else
	{
		while (env[++i])
		{
			env_node = malloc(sizeof(t_env_var));
			split_env(env_node, env[i]);
			new = ft_lstnew(env_node);
			ft_lstadd_back(&head, new);
		}
	}
	return (head);
}
