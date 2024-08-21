/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/08 21:01:15 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	fill_fd(t_list *lxrlst)
{
	while (lxrlst)
	{
		lxrlst->fd = -1;
		lxrlst = lxrlst->next;
	}
}

static int	extract_word(
	char *line_read,
	int i,
	t_list **lexer_list,
	t_gcollector *collector
)
{
	int		j;
	t_tok	token;

	j = 0;
	while (line_read[i + j] && (get_tok(line_read[i + j]) == NONE))
	{
		j += handle_quotes(line_read, i + j, '\"');
		j += handle_quotes(line_read, i + j, '\'');
		if (line_read[i + j] == ' '
			|| (line_read[i + j] > 8 && line_read[i + j] < 14))
			break ;
		else
			j++;
	}
	token = NONE;
	append_node(
		ftgc_substr(line_read, i, j, collector),
		token, lexer_list,
		collector
		);
	return (j);
}

void	tokenize_input(t_minishell *shell)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = ftgc_strtrim(shell->input, " ", &(shell->collector));
	free(shell->input);
	shell->input = tmp;
	i = 0;
	while (shell->input[i])
	{
		j = 0;
		i += ignore_spaces(shell->input, i);
		if (get_tok(shell->input[i]) != NONE)
			j = handle_token(
					shell->input, i,
					&shell->lexerlst,
					&shell->collector);
		else
			j = extract_word(
					shell->input, i,
					&shell->lexerlst,
					&shell->collector);
		i += j;
	}
	fill_fd(shell->lexerlst);
}
