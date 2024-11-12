/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:03:54 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/12 18:43:14 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signals_ignore(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signals_allow(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	check_key_un(char *str)
{
	int	i;

	i = 0;
	if (!str || is_space(str) || ft_isalpha(str[i]
			|| str[0] == '_'))
	{
		write(2, "minishell: unset: ", 18);
		write(2, str, ft_strlenn(str));
		write(2, " not a valid identifier\n", 24);
		return (0);
	}
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
		{
			write(2, "minishell: unset: ", 18);
			write(2, str, ft_strlenn(str));
			write(2, " not a valid identifier\n", 24);
			return (0);
		}
		i++;
	}
	return (1);
}
