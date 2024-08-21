/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/08 19:35:52 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_token(
	char *line_read,
	int i,
	t_list **lexer_list,
	t_gcollector *collector
)
{
	t_tok	token;

	token = get_tok(line_read[i]);
	if (token == TRUNCATE && get_tok(line_read[i + 1]) == TRUNCATE)
	{
		token = APPEND;
		append_node(NULL, token, lexer_list, collector);
		return (2);
	}
	else if (token == REDIRECT_INPUT
		&& get_tok(line_read[i + 1]) == REDIRECT_INPUT)
	{
		token = HEREDOC;
		append_node(NULL, token, lexer_list, collector);
		return (2);
	}
	else if (token != NONE)
	{
		append_node(NULL, token, lexer_list, collector);
		return (1);
	}
	return (-1);
}

int	handle_quotes(char *line_read, int i, char quote)
{
	int	j;

	j = 0;
	if (line_read[i + j] == quote)
		j++;
	else
		return (0);
	while (line_read[i + j] && line_read[i + j] != quote)
		j++;
	return (j);
}
