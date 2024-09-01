/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:59:29 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/01 16:38:36 by asebrani         ###   ########.fr       */
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
	strs = malloc(sizeof(char *) * (count_word + 1));
	if (!strs)
		return (NULL);
	while (n < count_word && *str)
	{
		while (*str && *str == sep)
			str++;
		strs[n] = return_word(str, sep);
		if (!strs[n])
			return (clear_strss(strs, n), NULL);
		while (*str && *str != sep)
			str++;
		n++;
	}
	strs[n] = NULL;
	return (strs);
}

void	copy_it(char *dest, char *src)
{	
	if(!src)
		return;
	while (*src)
		*(dest++) = *(src++);
	*dest = '\0';
}

char	*str_joiner(char *s1, char *s2)
{
	char	*ret;

	if (!s1)
		return (strdup(s2));
	if (!s2)
		return(strdup(s1));
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (NULL);
	copy_it(ret, s1);
	copy_it(ret + strlen(s1), s2);
	return (ret);
}


