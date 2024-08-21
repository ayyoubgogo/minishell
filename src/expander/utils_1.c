/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouhib <hmouhib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by hmouhib           #+#    #+#             */
/*   Updated: 2024/08/15 03:27:01 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief get's the index of the dollar sign !
 * @param str -
 * @return position of the dollar sign / 0 if not found !
 */
int	get_dsign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*delete_quotes(char *str, t_quote q)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == (int)q)
		{
			j = 0;
			while (str[i + j] == (int)q)
				j++;
			ft_strlcpy(
				&str[i],
				&str[i + j],
				ft_strlen(str) - i
				);
		}
		i++;
	}
	return (str);
}

char	*extend(t_minishell *shell, char *str)
{
	int		j;
	char	*temp;

	j = 0;
	temp = ftgc_strdup("", &shell->collector);
	shell->expand_code = NAY_EXPAND;
	while (j < ft_strlen(str))
	{
		j += handle_digits(j, str);
		if (str[j] == '$' && str[j + 1] == '?')
			j += expand_question_mark(shell, &temp, str);
		else if (str[j] == '$' && (str[j + 1] != ' '
				&& (str[j + 1] != '\"' || str[j + 2] != '\0'))
			&& str[j + 1] != '\0')
			j += expand_env(shell, str, &temp, j);
		else
			temp = ftgc_strjoin(
					temp, char_to_string(
						str[j++], &shell->collector),
					&shell->collector
					);
	}
	return (temp);
}
