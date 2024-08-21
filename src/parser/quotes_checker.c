/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/08 19:36:19 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
* @brief return's the index of the next quote !
 * @param str -
 * @param q quote either single or double
 * @return it's next position or the index of the last char
 */
static int	next_q(char const *str, char q)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != q)
		i++;
	return (i);
}

int	check_quotes(char const *lineread)
{
	int	i;
	int	j;

	i = 0;
	while (lineread[i])
	{
		if (lineread[i] == '\'' || lineread[i] == '\"')
		{
			j = next_q(&lineread[i + 1], lineread[i]);
			if (lineread[i + j + 1] != lineread[i])
				return (1);
			i += j + 1;
		}
		i++;
	}
	return (0);
}
