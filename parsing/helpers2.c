/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:27:48 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/12 21:10:25 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_str(char *dest, char *src)
{
	int	i;

	dest = c_malloc(sizeof(char) * (ft_strlenn(src) + 1), 1);
	i = 0;
	if (!src)
		return (NULL);
	while (*src)
	{
		dest[i] = *src;
		i++;
		src++;
	}
	dest[i] = '\0';
	return (dest);
}

int	pass_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

int	pass_spaces_end(char *input)
{
	int	i;

	i = ft_strlenn(input);
	while (input[i] == ' ' || input[i] == '\t')
		i--;
	return (i);
}

void	copy_without_spaces(char *dst, char *src)
{
	int	i;
	int	j;
	int	k;

	i = pass_spaces(src);
	j = ft_strlenn(src) - 1;
	k = 0;
	if (!src && !*src)
		return ;
	while (src[j] == ' ' || src[j] == '\t')
		j--;
	while (i <= j)
	{
		dst[k] = src[i];
		i++;
		k++;
	}
	dst[k] = '\0';
}
