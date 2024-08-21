/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:08:28 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/13 13:50:53 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	del_the_env(t_minishell *shell, t_list *lst)
{
	t_list	*tmp;

	tmp = shell->envlst;
	while (tmp->next != lst)
		tmp = tmp->next;
	if (tmp->next)
		tmp->next = lst->next;
	else
		tmp->next = NULL;
	free(((t_env *)(lst->content))->key);
	free(((t_env *)(lst->content))->val);
	ft_lstdelone(lst, del);
}

t_list	*get_the_env(char *key, t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strncmp(((t_env *)(tmp->content))->key, key,
			ft_strlen(key)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	o_check_key(char *str, t_list *list)
{
	char	*key;

	while (list)
	{
		key = ((t_env *)(list->content))->key;
		if (ft_strncmp(key, str, ft_strlen(key)) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}

void	unset(char **str, t_minishell *shell)
{
	t_list	*lst;
	int		i;

	i = 1;
	while (str[i])
	{
		if (o_check_key(str[i], shell->envlst) == 1)
		{
			lst = get_the_env(str[i], shell->envlst);
			del_the_env(shell, lst);
		}
		i++;
	}
}
