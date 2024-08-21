/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:36:22 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/15 12:03:34 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_add_export(char *str, t_list *list, char *tst, int len)
{
	char	*env[2];

	env[0] = ft_substr(str, 0, len - ft_strlen(tst));
	env[1] = ft_strdup(tst + 2);
	if (check_char(env[0]) == 0)
	{
		ft_putstr_fd("export: `-", 2);
		ft_putstr_fd(env[0], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_ec = 1;
	}
	else
	{
		if (check_key(list, env[0], env[1]) == 1)
			add_val(list, env[0], env[1]);
		else
			add_back_to_env(list, env[0], env[1]);
	}
	free(env[0]);
	free(env[1]);
}

int	check_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	check_equality_exp(char *str, t_list *list, int len, t_minishell *shell)
{
	char	*env[2];

	(void)shell;
	env[0] = ft_substr(str, 0, len);
	env[1] = NULL;
	if (check_char(env[0]) == 0)
	{
		ft_putstr_fd("export: `-", 2);
		ft_putstr_fd(env[0], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_ec = 1;
	}
	else
	{
		if (check_key(list, env[0], env[1]) == 1)
			change_val(list, env[0], env[1]);
		else
			add_back_to_env(list, env[0], env[1]);
	}
	free(env[0]);
}
