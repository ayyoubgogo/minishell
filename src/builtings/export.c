/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:28:19 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/15 11:09:15 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_val(t_list *list, char *key, char *val)
{
	t_list	*tmp;
	char	*env_var;
	char	*value;

	tmp = list;
	while (tmp)
	{
		env_var = ((t_env *)tmp->content)->key;
		if (ft_strnstr(env_var, key, ft_strlen(key))
			&& ft_strlen(env_var) == ft_strlen(key))
		{
			value = ((t_env *)tmp->content)->val;
			((t_env *)tmp->content)->val = ft_strjoin(value, val);
		}
		tmp = tmp->next;
	}
}

int	equal_issue(char *str, t_minishell *shell)
{
	(void)shell;
	if (str[0] == '=' && str[1] == '\0')
	{
		ft_putstr_fd("minishell: export: `=': not a valid identifier\n", 2);
		g_ec = 1;
		return (1);
	}
	else if (str[0] == '=' && str[1])
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_ec = 1;
		return (1);
	}
	return (0);
}

void	export_var(char *str, t_list *list, t_minishell *shell)
{
	int		len;
	int		s;
	char	*tst;

	len = ft_strlen(str);
	tst = ft_strnstr(str, "+=", len);
	s = check_equal(str);
	if (equal_issue(str, shell))
		return ;
	if (tst)
		check_add_export(str, list, tst, len);
	else if (s == 0)
		check_equality_exp(str, list, len, shell);
	else if (s == 1)
		double_quote_expo(str, list, len);
}

void	check_export(char **str, t_list *list, t_minishell *shell)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = check_string(str[i]);
		if (j == 0)
		{
			ft_putstr_fd("minishell:", 2);
			ft_putstr_fd(" export:`", 2);
			ft_putstr_fd(str[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_ec = 1;
		}
		else
			export_var(str[i], list, shell);
		i++;
	}
}

void	export(char **str, t_list *list, t_minishell *shell)
{
	if (str[1] == NULL)
		declare(list);
	else if (str[1])
	{
		check_export(str, list, shell);
	}
}
