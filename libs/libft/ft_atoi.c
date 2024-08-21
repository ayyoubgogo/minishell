/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:37:53 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/12 23:24:31 by maomao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	count;
	int	negative;
	int	number;

	count = 0;
	negative = 0;
	number = 0;
	while ((str[count] != '\0') && (str[count] < 48 || str[count] > 57))
	{
		if (str[count] == '-')
			negative++;
		count++;
	}
	while (str[count] >= 48 && str[count] <= 57)
	{
		number = number * 10 + str[count] - 48;
		count++;
	}
	if (negative % 2 == 1)
		return (number * -1);
	return (number);
}
