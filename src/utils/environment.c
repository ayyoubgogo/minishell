/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/08 20:39:54 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <minishell.h>

static void	set_length(
	int *key_length,
	int *value_length,
	char *estr
)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (estr[i] && estr[i] != '=')
		i++;
	*key_length = i++;
	while (estr[i + j])
		j++;
	*value_length = j;
}

static t_env_var	*get_env(char *estr)
{
	int			val_len;
	int			key_len;
	int			i;
	int			j;
	t_env_var	*env;

	set_length(&key_len, &val_len, estr);
	env = (t_env_var *)malloc(sizeof(t_env_var));
	ft_bzero((void *)env, sizeof(t_env_var));
	env->key = (char *)malloc(key_len + 1);
	ft_bzero((void *)env->key, key_len + 1);
	env->val = (char *)malloc(val_len + 1);
	ft_bzero((void *)env->val, val_len + 1);
	i = 0;
	while (estr[i] && estr[i] != '=')
	{
		env->key[i] = estr[i];
		i++;
	}
	j = 0;
	while (estr[++i])
		env->val[j++] = estr[i];
	return (env);
}

t_list	*init_env(char **envp)
{
	int		i;
	t_list	*lst;
	t_list	*head;

	i = 0;
	lst = NULL;
	head = NULL;
	while (envp[i])
	{
		if (lst == NULL)
		{
			lst = ft_lstnew((void *)get_env(envp[i]));
			head = lst;
		}
		else
		{
			lst->next = ft_lstnew(
					(void *)get_env(envp[i]));
			lst = lst->next;
		}
		i++;
	}
	return (head);
}

char	*ms_get_env(t_list *envlst, char *key)
{
	t_list	*elst;

	if (envlst == NULL || key == NULL)
		return (NULL);
	elst = envlst;
	if (key[0] == '$')
		key = &key[1];
	while (elst)
	{
		if (!ft_strncmp(
				key,
				((t_env_var *)(elst->content))->key, ft_strlen(key) + 1
		))
			return ((((t_env_var *)(elst->content)))->val);
		elst = elst->next;
	}
	return ("");
}
