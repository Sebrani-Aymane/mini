/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:51:54 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/30 21:29:44 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	check_for_delimeter(t_node *tokens)
{
	t_node	*current;

	current = tokens;
	while (current && current->next)
	{
		if (!strcmp(current->content, "<<")
			&& (strchr(current->next->content, '\'')
				|| strchr(current->next->content, '"')))
			current->next->delimeter_inside_quotes = 1;
		else
			current->next->delimeter_inside_quotes = 0;
		current = current->next;
	}
}
void	add_node(t_node **list, char *content)
{
	t_node	*new_node;

	new_node = ft_lstnew(content);
	if (!new_node)
		return ;
	ft_lstadd_back(list, new_node);
}

void	add_token(t_node **list, char *content, int start, int end)
{
	int		len;
	char	*token;

	len = end - start;
	token = c_malloc((sizeof(char) * (len + 1)), 1);
	if (!token)
		return ;
	strncpy(token, content + start, len);
	token[len] = '\0';
	add_node(list, token);
}