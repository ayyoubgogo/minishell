/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:15:03 by agaougao          #+#    #+#             */
/*   Updated: 2024/08/09 20:55:22 by hmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_env(t_list *env, t_minishell *shell)
{
	if (env->next == NULL)
	{
		printf("%s\n", shell->pwd);
		printf("SHLVL=1\n");
		printf("_=/usr/bin/env\n");
	}
	else
	{
		while (env)
		{
			if (((t_env *)env->content)->val)
			{
				printf("%s", ((t_env *)env->content)->key);
				if (ft_strncmp(((t_env *)env->content)->val, "\"\"",
						ft_strlen(((t_env *)env->content)->val)))
					printf("=%s", ((t_env *)env->content)->val);
				else
					printf("=");
				printf("\n");
			}
			env = env->next;
		}
	}
}
