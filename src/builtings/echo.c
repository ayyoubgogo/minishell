/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:57:23 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/13 18:37:26 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	echo_help(char **str, int i)
{
	while (str[i])
	{
		if (ft_strncmp(str[i], "-n", 2) != 0)
			break ;
		else
			i++;
	}
	if (str[i] != NULL)
	{
		while (str[i])
		{
			printf("%s", str[i]);
			if (str[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
}

void	echo(char **str, t_minishell *shell)
{
	int	i;

	(void)shell;
	i = 1;
	if (str[1] == NULL)
		printf("\n");
	else if (ft_strncmp(str[1], "-n", 2) == 0)
	{
		echo_help(str, i);
	}
	else
	{
		while (str[i])
		{
			printf("%s", str[i]);
			if (str[i + 1] != NULL)
				printf(" ");
			i++;
		}
		printf("\n");
	}
	g_ec = 0;
}
