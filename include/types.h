/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/12 16:43:17 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <libft.h>
# include <gcollector.h>

# define PROMPT "minishell$ "
# define NAY_EXPAND 0x0000
# define AYE_EXPAND 0x0001

/**
 * @brief	a enum type that indicates the token type
 *			wether a PIPE, TRUNCATE, APPEND,
 *			REDIRECT INPUT, HEREDOC, or NONE !
 */
typedef enum e_tok
{
	PIPE = 1,		// |
	TRUNCATE,		// >
	APPEND,			// >>
	REDIRECT_INPUT,	// <
	HEREDOC,		// <<
	NONE
}	t_tok;

typedef enum e_quote
{
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"'
}	t_quote;

typedef struct s_env_var
{
	char	*key;
	char	*val;
}	t_env_var;

typedef struct s_token
{
	int		key;
	char	*word;
	t_tok	token;
}	t_token;

typedef struct s_minishell
{
	int				expand_code;
	int				stat;
	int				pid;
	int				exit_status;
	int				hd_expand;
	char			*oldpwd;
	char			*pwd;
	char			*input;
	t_list			*envlst;
	t_list			*lexerlst;
	t_list			*commands;
	t_gcollector	collector;
}	t_minishell;

typedef struct s_parser
{
	t_list		*lexer_list;
	t_list		*redirections;
	int			redirections_count;
	char		*error_message;
}	t_parser;

typedef struct s_command
{
	int			expanded;
	char		**cmd_argv;
	int			cmd_argc;
	t_list		*redirections;
	int			redirections_count;
}	t_command;

typedef t_env_var	t_env;

#endif