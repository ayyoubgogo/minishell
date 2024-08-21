/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/15 19:49:14 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <types.h>
# include <unistd.h>

extern int	g_ec;

void		builting(char **str, t_minishell *shell);
int			count_str(char **str);
void		miniexit(char **str, t_minishell *shell);
void		cd(char **str, t_minishell *shell);
void		pwd(t_minishell *shell);
void		mini_env(t_list *env, t_minishell *shell);
void		echo(char **str, t_minishell *shell);
void		dup_to_out(t_command *command);
void		ft_free_tab(char **env);
int			check_char(char *str);
void		check_path(char *path, char **str, t_minishell *shell, char **env);
t_list		*env_list(char **env);
void		export(char **str, t_list *list, t_minishell *shell);
void		split_env(t_env_var *env_node, char *str);
void		unset(char **str, t_minishell *shell);
char		*check_exist_path(t_list *tmp);
char		*check_valid_path(char **ptr, char **str);
int			check_pipe(t_minishell *shell);
char		**turn_env_tab(t_minishell *shell);
void		pipex(t_minishell *shell, t_command *command,
				t_command *nex_command);
int			check_builtin(char *str);
void		red_out(t_minishell *shell, t_command *cmd);
void		run_builting(char **str, t_minishell *shell, int i);
void		check(t_minishell *shell, t_command *command);
void		red_in(t_minishell *shell, t_command *command);
int			redirection(t_minishell *shell);
int			check_red(t_minishell *shell, t_command *command);
char		*join_strings(char **cmd);
int			here_doc(t_minishell *shell, t_command *command);
void		append_red(t_minishell *shell, t_command *command);
int			check_some(t_command *command, t_minishell *shell);
int			here_doc_count(t_minishell *shell);
void		check_add_export(char *str, t_list *list, char *tst, int len);
void		add_back_to_env(t_list *list, char *key, char *val);
void		add_val(t_list *list, char *key, char *val);
int			check_key(t_list *list, char *key, char *val);
void		cd_c(char *path, t_minishell *shell);
void		errors(char **str, t_minishell *shell, char **env);
char		*ft_getenv(char *str, t_list *list);
void		run_so_bui(t_command *command, t_minishell *shell);
void		check_equality_exp(char *str, t_list *list, int len,
				t_minishell *shell);
void		change_val(t_list *list, char *key, char *val);
void		double_quote_expo(char *str, t_list *list, int len);
void		add_back_to_env(t_list *list, char *key, char *val);
int			check_equal(char *str);
int			check_string(char *str);
void		declare(t_list *env);
int			check_key(t_list *list, char *key, char *val);
int			check_so_bui(t_command *command);
void		dup_in_out(int in, int out);
int			*sgl(int n);
void		fake_hd_handler(int sig);
t_list		*init_env(char **envp);
char		*ms_get_env(t_list *envlst, char *key);
void		clear_envlst(t_list **env_list, void (*del)(t_env_var *));
void		env_del(t_env_var *env);
void		hd_handler(int sig);
void		handler(int sig);
void		init_minishell(t_minishell *shell_struct, char **envp);
void		shell_loop(t_minishell *shell, t_gcollector **collector,
				char **envp);
int			check_quotes(char const *lineread);
void		tokenize_input(t_minishell *shell);
int			handle_token(char *line_read, int i, t_list **lexer_list,
				t_gcollector *collector);
int			handle_quotes(char *line_read, int i, char quote);
t_tok		get_tok(char c);
int			ignore_spaces(char *str, int i);
int			append_node(char *word, t_tok token, t_list **lexer_list,
				t_gcollector *collector);
void		clear_first_node(t_list **lexer_list);
void		lexer_delone(t_list **lexer_list, int key);
int			parser(t_minishell *shell);
int			raise_pipe_error(t_minishell *shell, int n);
int			count_args(t_list *lexer_list);
void		setup_parser_struct(t_list *lexerlst, t_parser **parser_,
				t_gcollector *collector);
char		**parse_args(t_parser *parser, t_gcollector *collector);
int			check_pipe_syntax(t_minishell *shell, t_tok token);
t_command	*command_new(char **argv_, t_list *redcs, int redcs_count,
				t_gcollector *collector);
void		redirection_new(t_parser *parser, t_list *node,
				t_gcollector *collector);
int			expand_env(t_minishell *shell, char *str, char **tmp, int i);
int			after_dol_lenght(char *str, int j);
int			expand_question_mark(t_minishell *shell, char **str, char *oristr);
int			handle_digits(int j, char *str);
char		*char_to_string(char c, t_gcollector *collector);
int			get_dsign(char *str);
char		*delete_quotes(char *str, t_quote q);
char		*extend(t_minishell *shell, char *str);
void		expand(t_minishell *shell, char **av_, t_command *command);
char		*expand_string(t_minishell *shell, char *word);
void		expander(t_minishell *shell);

char		**ftgc_tab_join(char **tab, int size, char *str,
				t_gcollector *collector);
void		filter_cmds(t_minishell *shell);
void		filter_check(t_minishell *shell, char **ex_temp, char **av, int k);

#endif
