/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:48:07 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/13 18:36:24 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_digit(char **str)
{
	int	i;

	i = 0;
	while (str[1][i])
	{
		while (str[1][i] == '-' || str[1][i] == '+')
			i++;
		if (ft_isdigit(str[1][i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char **str)
{
	int	n;

	if (check_digit(str) == 0)
	{
		n = ft_atoi(str[1]);
		exit(n);
	}
	else
	{
		ft_putstr_fd("minishell : exit ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putstr_fd(" : numeric argument required\n", 2);
		exit(2);
	}
}

int	count_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	miniexit(char **str, t_minishell *shell)
{
	(void)shell;
	if (count_str(str) < 3)
	{
		printf("exit\n");
		if (str[1])
			ft_exit(str);
		else
			exit(0);
	}
	else
	{
		ft_putstr_fd(" too many arguments\n", 2);
		g_ec = 1;
	}
}
