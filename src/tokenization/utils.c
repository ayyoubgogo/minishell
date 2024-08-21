/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/08 21:15:56 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tok	get_tok(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (TRUNCATE);
	else if (c == '<')
		return (REDIRECT_INPUT);
	else
		return (NONE);
}

int	ignore_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] == ' '
		|| (str[i + j] > 8 && str[i + j] < 14))
		j++;
	return (j);
}

int	append_node(
	char *word,
	t_tok token,
	t_list **lexer_list,
	t_gcollector *collector
)
{
	t_list		*node;
	t_token		*content;
	static int	tracker;

	content = (t_token *)gc_malloc(collector, sizeof(t_token));
	if (content == NULL)
		return (0);
	content->token = token;
	content->word = word;
	content->key = tracker++;
	node = ftgc_lstnew((void *)content, collector);
	if (node == NULL)
		return (0);
	if (*lexer_list == NULL)
		*lexer_list = node;
	else
		ft_lstadd_back(lexer_list, node);
	return (1);
}
