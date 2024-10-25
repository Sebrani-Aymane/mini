/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:59:29 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/25 20:07:47 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split(char *str, char sep)
{
	int		count_word;
	int		n;
	char	**strs;

	if (!str)
		return (NULL);
	n = 0;
	count_word = count_words(str, sep);
	strs = c_malloc(sizeof(char *) * (count_word + 1), 1);
	if (!strs)
		return (NULL);
	while (n < count_word && *str)
	{
		while (*str && *str == sep)
			str++;
		strs[n] = return_word(str, sep);
		if (!strs[n])
			return (NULL);
		while (*str && *str != sep)
			str++;
		n++;
	}
	strs[n] = NULL;
	return (strs);
}

void	copy_it(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*str_joiner(char *s1, char *s2)
{
	char	*ret;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ret = c_malloc(sizeof(char) * (ft_strlenn(s1) + ft_strlenn(s2) + 1), 1);
	if (!ret)
		return (NULL);
	copy_it(ret, s1);
	copy_it(ret + strlen(s1), s2);
	return (ret);
}

int	ft_isalpha(int c)
{
	if ((c <= 122 && c >= 97) || (c <= 90 && c >= 65))
		return (1);
	else
		return (0);
}

int	is_space(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		return (1);
	return (0);
}
