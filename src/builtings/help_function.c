/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:26:59 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/09 20:57:01 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_back_to_env(t_list *list, char *key, char *val)
{
	t_env	*env;
	t_list	*new;

	env = (t_env *)malloc(sizeof(t_env));
	env->key = ft_strdup(key);
	if (val == NULL)
		env->val = NULL;
	else if (val[0] == '\0')
		env->val = strdup("\"\"");
	else
		env->val = ft_strdup(val);
	new = ft_lstnew(env);
	ft_lstadd_back(&list, new);
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	change_val(t_list *list, char *key, char *val)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strncmp(((t_env *)tmp->content)->key, key, ft_strlen(key)) == 0)
		{
			if (val != NULL)
			{
				if (val[0] != '\0')
				{
					free(((t_env *)tmp->content)->val);
					((t_env *)tmp->content)->val = ft_strdup(val);
				}
				else if (val[0] == '\0')
				{
					free(((t_env *)tmp->content)->val);
					((t_env *)tmp->content)->val = strdup("\"\"");
				}
			}
		}
		tmp = tmp->next;
	}
}

int	check_string(char *str)
{
	if (ft_isdigit(str[0]))
	{
		return (0);
	}
	return (1);
}
