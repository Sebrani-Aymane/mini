/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:25:24 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/26 01:03:29 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	when_not_blt(t_line *final, char **env, env_vars *list)
{
	int	i;

	i = 0;
	i = excutefilepath(final, list, env);
	if (i == 2)
	{
		if (final->tokens->type == 1 || final->tokens->type == 2)
		{
			exit_status(1, i);
			write(2, final->tokens->content,
				ft_strlenn(final->tokens->content));
			write(2, ": No such file or directoory\n", 28);
			c_malloc(0, 0);
			exit(128);
		}
	}
}
