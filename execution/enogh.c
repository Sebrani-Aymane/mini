/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enogh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:41:05 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/23 06:01:39 by asebrani         ###   ########.fr       */
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

	i = 0;
	if (!str || !*str)
		return(1);
	while (str && str[i] && str1[i] && (str[i] == str1[i]))
		i++;
	return (str[i] - str1[i]);
}

int	ft_listsize(t_line *lst)
{
	int	i;
	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int is_dir(char *path)
{
    struct stat statbuf;

    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

void	ft_putstr(char *s, int fd)
{
	if (!s || !*s)
		return;
	write(fd, s, ft_strlenn(s));
}

// int	ft_isdigit(int c)
// {
// 	if (c <= '9' && c >= '0')
// 		return (1);
// 	else
// 		return (0);
// }
