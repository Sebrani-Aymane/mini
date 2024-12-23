/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enogh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:41:05 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/07 12:26:36 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	if (!str || !str1)
		return (-1);
	i = 0;
	while (str[i] && str1[i] && str[i] == str1[i])
		i++;
	return (str[i] - str1[i]);
}

int	ft_listsize(t_line *lst)
{
	int	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->next)
		{
			lst = lst->next;
			i++;
		}
		else
			return (i);
	}
	return (i);
}

int	is_dir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	ft_putstr(char *s, int fd)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlenn(s);
	write(fd, s, len);
}
