/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enogh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:41:05 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/17 20:42:37 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ret(char *in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if (in[i] == '+')
			in[i] = in[i + 1];
		i++;
	}
	return (in);
}

int	ft_isalnum(int c)
{
	if (((c <= 122 && c >= 97) || (c <= 90 && c >= 65)))
		return (1);
	else
		return (0);
}

int	ft_strcmp(char *str, char *str1)
{
	int	i;

	i = 0;
	while (str[i] && str1[i] && (str[i] == str1[i]))
		i++;
	return (str[i] - str1[i]);
}
