/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:32:44 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/08 20:38:21 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (s1[0] == '\0' && s2[0] == '\0')
		return ((char *)s1);
	while (s1[i] != '\0')
	{
		j = 0;
		while (s2[j] != '\0' && s1[i + j] == s2[j])
			j++;
		if (s2[j] == '\0')
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strrncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1)
		return (-1);
	while (i < n - 1 && s1[i] == s2[i] && s2[i] && s1[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

void	conf_inside_quotes(t_node *tokens)
{
	t_node	*curr;

	curr = tokens;
	while (curr)
	{
		if (inside_quotes(curr->content))
			curr->inside_quotes = 1;
		else
			curr->inside_quotes = 0;
		curr = curr->next;
	}
}

char	*join_tokens(t_list *shell)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	if (!shell->tokens)
		return (NULL);
	while (shell->tokens[i])
	{
		str = ft_strjoin(str, shell->tokens[i]->content);
		if (shell->tokens[i + 1])
			str = ft_strjoin(str, " ");
		i++;
	}
	if (!str)
		return (NULL);
	return (str);
}
