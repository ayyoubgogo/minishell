/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/08 20:15:32 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_args(t_list *lexer_list)
{
	int	ac;

	ac = 0;
	if (lexer_list == NULL)
		return (ac);
	while (lexer_list && ((t_token *)(lexer_list->content))
		->token != PIPE)
	{
		ac++;
		lexer_list = lexer_list->next;
	}
	return (ac);
}

void	setup_parser_struct(
	t_list *lexerlst,
	t_parser **parser_,
	t_gcollector *collector
)
{
	t_parser	*parser;

	parser = (t_parser *)gc_malloc(collector, sizeof(t_parser));
	parser->error_message = NULL;
	parser->lexer_list = lexerlst;
	parser->redirections_count = 0;
	parser->redirections = NULL;
	*parser_ = parser;
}

char	**parse_args(
	t_parser *parser,
	t_gcollector *collector
)
{
	char	**argv_;
	int		i;
	int		args_count;
	t_list	*cur;

	i = 0;
	cur = parser->lexer_list;
	args_count = count_args(parser->lexer_list);
	argv_ = ftgc_calloc((args_count + 1), sizeof(char *), collector);
	while (args_count > 0)
	{
		if (((t_token *)(cur->content))->word != NULL)
		{
			argv_[i++] = ftgc_strdup(
					((t_token *)(cur->content))->word, collector);
			lexer_delone(
				&parser->lexer_list, ((t_token *)(cur->content))->key);
			cur = parser->lexer_list;
		}
		args_count--;
	}
	return (argv_);
}

t_command	*command_new(
	char **argv_,
	t_list *redcs,
	int redcs_count,
	t_gcollector *collector
)
{
	t_command	*cmd;
	int			ac;

	ac = 0;
	while (argv_[ac])
		ac++;
	cmd = (t_command *)gc_malloc(
			collector, sizeof(t_command));
	cmd->redirections = redcs;
	cmd->cmd_argv = argv_;
	cmd->cmd_argc = ac;
	cmd->redirections_count = redcs_count;
	return (cmd);
}

void	redirection_new(t_parser *parser, t_list *node, t_gcollector *collector)
{
	t_token	*redirection_node;
	int		i_nodes[2];

	i_nodes[0] = ((t_token *)(node->content))->key;
	i_nodes[1] = ((t_token *)(node->next->content))->key;
	redirection_node = (t_token *)gc_malloc(collector, sizeof(t_token));
	ft_bzero(redirection_node, sizeof(t_token));
	redirection_node->key = -1;
	redirection_node->word = ftgc_strdup(
			((t_token *)(node->next->content))->word,
			collector
			);
	redirection_node->token = ((t_token *)(node->content))->token;
	lexer_delone(&parser->lexer_list, i_nodes[0]);
	lexer_delone(&parser->lexer_list, i_nodes[1]);
	parser->redirections_count++;
	ft_lstadd_back(
		&parser->redirections,
		ftgc_lstnew(redirection_node, collector)
		);
}
