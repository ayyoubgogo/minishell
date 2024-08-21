/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/15 03:18:52 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_quote	is_quoted(const char *delimiter)
{
	int	e;

	e = ft_strlen(delimiter) - 1;
	if (delimiter[0] == SINGLE_QUOTE && delimiter[e] == SINGLE_QUOTE)
		return (SINGLE_QUOTE);
	else if (delimiter[0] == DOUBLE_QUOTE && delimiter[e] == DOUBLE_QUOTE)
		return (DOUBLE_QUOTE);
	return (-1);
}

static void	check_quoting(int i, char **av_)
{
	if (!(is_quoted(av_[i]) == SINGLE_QUOTE
			|| is_quoted(av_[i]) == DOUBLE_QUOTE))
	{
		av_[i] = delete_quotes(av_[i], SINGLE_QUOTE);
		av_[i] = delete_quotes(av_[i], DOUBLE_QUOTE);
	}
	else if (is_quoted(av_[i]) == SINGLE_QUOTE)
		av_[i] = delete_quotes(av_[i], SINGLE_QUOTE);
	else if (is_quoted(av_[i]) == DOUBLE_QUOTE)
		av_[i] = delete_quotes(av_[i], DOUBLE_QUOTE);
}

/**
 *
 * @param shell minishell struct !
 * @param av_ command arguments !
 */
void	expand(t_minishell *shell, char **av_, t_command *command)
{
	int		i;
	int		before_ds;
	int		dollar_sign_index;
	char	*temp;

	(void)command;
	i = -1;
	while (av_[++i])
	{
		if (is_quoted(av_[i]) == SINGLE_QUOTE)
		{
			av_[i] = delete_quotes(av_[i], SINGLE_QUOTE);
			continue ;
		}
		dollar_sign_index = get_dsign(av_[i]);
		before_ds = 1;
		if (dollar_sign_index > 1)
			before_ds = av_[i][dollar_sign_index - 2] != '\'';
		if (before_ds && av_[i][dollar_sign_index] != '\0')
			filter_check(shell, &temp, av_, i);
		if (ft_strncmp(av_[0], "export", ft_strlen(av_[0]) - 1) != 0)
			check_quoting(i, av_);
	}
}

/**
 *
 * @param shell minishell struct
 * @param word the string to expand !
 * @return
 */
char	*expand_string(t_minishell *shell, char *word)
{
	char	*tmp;
	int		ds;
	int		before_ds;

	tmp = NULL;
	ds = get_dsign(word);
	before_ds = 1;
	if (ds > 1)
		before_ds = word[ds - 2] != '\'';
	if (before_ds && word[ds] != '\0')
	{
		tmp = extend(shell, word);
		word = tmp;
	}
	word = delete_quotes(word, SINGLE_QUOTE);
	word = delete_quotes(word, DOUBLE_QUOTE);
	return (word);
}

/**
 * expanding the dollar sign ...
 * @param shell minishell's struct
 */
void	expander(t_minishell *shell)
{
	t_list		*rd_startp;
	t_list		*commands_list;
	t_token		*current_token;
	t_command	*current_command;

	commands_list = shell->commands;
	while (commands_list)
	{
		current_command = commands_list->content;
		rd_startp = current_command->redirections;
		expand(shell, current_command->cmd_argv, current_command);
		while (current_command->redirections)
		{
			current_token = current_command->redirections->content;
			if (current_token->token != HEREDOC)
				current_token->word = expand_string(shell, current_token->word);
			current_command->redirections = current_command->redirections->next;
		}
		current_command->redirections = rd_startp;
		commands_list = commands_list->next;
	}
}
