/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/13 14:51:58 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	perform_export_checks(
	t_list *lexlst,
	t_parser *parser,
	t_gcollector *collector
)
{
	if (lexlst->next == NULL)
	{
		parser->error_message = ftgc_strdup(
				"syntax error: unexpected token near \'\\n\'", collector);
		lexer_delone(&parser->lexer_list, ((t_token *)(lexlst->content))->key);
		return (-1);
	}
	if (((t_token *)(lexlst->next->content))->token != NONE)
	{
		parser->error_message = ftgc_strdup(
				"syntax error: near unexpected token", collector);
		lexer_delone(&parser->lexer_list, ((t_token *)(lexlst->content))->key);
		lexer_delone(
			&parser->lexer_list,
			((t_token *)(lexlst->next->content))->key
			);
		return (-1);
	}
	return (0);
}

static int	export_redirections(t_parser *parser, t_gcollector *collector)
{
	t_list	*lexlst;

	lexlst = parser->lexer_list;
	while (lexlst && ((t_token *)(lexlst->content))->token == NONE)
		lexlst = lexlst->next;
	if (lexlst == NULL || ((t_token *)(lexlst->content))->token == PIPE)
		return (0);
	if (perform_export_checks(lexlst, parser, collector) == -1)
		return (-1);
	if (((t_token *)(lexlst->content))->token >= TRUNCATE
		&& ((t_token *)(lexlst->content))->token <= HEREDOC)
		redirection_new(parser, lexlst, collector);
	if (export_redirections(parser, collector) == -1)
		return (-1);
	return (0);
}

static t_command	*fetch_command(
	t_parser *parsing_data,
	t_gcollector *collector
)
{
	char	**argv_;

	if (export_redirections(parsing_data, collector) < 0)
	{
		if (parsing_data->error_message)
			ft_putstr_fd(ftgc_strjoin(
					parsing_data->error_message, "\n", collector), 2);
		return (NULL);
	}
	argv_ = parse_args(parsing_data, collector);
	return (command_new(
			argv_, parsing_data->redirections,
			parsing_data->redirections_count, collector));
}

static void	parse_command(t_minishell *shell, t_parser *parser_)
{
	t_command	*cmd;

	cmd = fetch_command(parser_, &shell->collector);
	if (cmd == NULL)
	{
		shell->lexerlst = NULL;
		shell->commands = NULL;
		parser_->lexer_list = NULL;
		g_ec = 2;
	}
	else
		ft_lstadd_back(
			&shell->commands,
			ftgc_lstnew(cmd, &shell->collector));
}

int	parser(t_minishell *shell)
{
	t_parser	*parser_struct;
	t_token		*data;

	shell->commands = NULL;
	if (((t_token *)(shell->lexerlst->content))->token == PIPE)
		return (raise_pipe_error(shell, -1));
	while (shell->lexerlst)
	{
		data = (t_token *)(shell->lexerlst->content);
		if (shell->lexerlst && data->token == PIPE)
		{
			lexer_delone(&shell->lexerlst,
				((t_token *)(shell->lexerlst->content))->key);
			if (shell->lexerlst == NULL)
				return (raise_pipe_error(shell, 1));
		}
		if (check_pipe_syntax(
				shell, ((t_token *)(shell->lexerlst->content))->token))
			return (1);
		setup_parser_struct(shell->lexerlst, &parser_struct, &shell->collector);
		parse_command(shell, parser_struct);
		shell->lexerlst = parser_struct->lexer_list;
	}
	return (0);
}
