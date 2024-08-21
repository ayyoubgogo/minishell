/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/10 14:02:41 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	env_del(t_env_var *env)
{
	free(env->key);
	free(env->val);
	free(env);
}

void	clear_envlst(t_list **env_list, void (*del)(t_env_var *))
{
	t_list	*temp;

	temp = NULL;
	while (*env_list)
	{
		temp = (*env_list)->next;
		del((*env_list)->content);
		free(*env_list);
		*env_list = temp;
	}
}

void	clear_first_node(t_list **lexer_list)
{
	*lexer_list = (*lexer_list)->next;
	if (*lexer_list)
		(*lexer_list)->prev = NULL;
}

void	lexer_delone(t_list **lexer_list, int key)
{
	t_list	*target;
	t_list	*p;

	if (((t_token *)(*lexer_list)->content)->key == key)
	{
		clear_first_node(lexer_list);
		return ;
	}
	target = *lexer_list;
	while (target && ((t_token *)(target->content))->key != key)
	{
		p = target;
		target = target->next;
	}
	if (target == NULL)
		return ;
	p->next = target->next;
	if (p->next != NULL)
		p->next->prev = p;
}
