/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/13 21:33:57 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief expand the environment variable !
 * @param shell minishell struct ...
 * @param str the string to read from (expand)
 * @param tmp the string to write to (save the expanded string to)
 * @param i dollar sign index !
 * @return
 * i wanna skip n characters => the <$env_var_key> from the original string !
 */
int	expand_env(t_minishell *shell, char *str, char **tmp, int i)
{
	char	*env_val;
	char	*env_key;
	int		ret_;
	int		adl;

	ret_ = 0;
	adl = after_dol_lenght(str, i) - i;
	env_key = ftgc_substr(str, i, adl, &shell->collector);
	env_val = ms_get_env(shell->envlst, env_key);
	if (env_val)
	{
		env_val = delete_quotes(env_val, DOUBLE_QUOTE);
		*tmp = ftgc_strjoin(*tmp, env_val, &shell->collector);
		ret_ = ft_strlen(env_key);
		shell->expand_code = AYE_EXPAND;
	}
	return (ret_);
}

int	after_dol_lenght(char *str, int j)
{
	int	i;

	i = j + 1;
	while (ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i]))
		i++;
	return (i);
}

/** expand the $?, replacing it with the exit_status_code ! */
int	expand_question_mark(
	t_minishell *shell,
	char **str,
	char *oristr
)
{
	char	*ec;

	(void)oristr;
	ec = ft_itoa(g_ec);
	*str = ftgc_strjoin(*str, ec, &shell->collector);
	free(ec);
	shell->expand_code = AYE_EXPAND;
	return (2);
}

int	handle_digits(int j, char *str)
{
	int	i;

	i = j;
	if (str[j] == '$')
	{
		if (ft_isdigit(str[j + 1]) == 1)
			j += 2;
	}
	return (j - i);
}

char	*char_to_string(char c, t_gcollector *collector)
{
	char	*str;

	str = ftgc_calloc(2, sizeof(char), collector);
	str[0] = c;
	return (str);
}
