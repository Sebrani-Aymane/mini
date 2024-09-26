/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:51:54 by cbajji            #+#    #+#             */
/*   Updated: 2024/09/25 17:10:19 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection_op(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	more_than_op(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			while (input[i] == '<' || input[i] == '>')
			{
				count++;
				i++;
				if (count > 2)
					return (i);
			}
		}
		count = 0;
		i++;
	}
	return (0);
}

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

void	check_token_dollar(t_token **token)
{
	int	i;

	i = 0;
	while (token && token[i])
	{
		if (token[i]->content && ft_strchr(token[i]->content, '$'))
			token[i]->need_expand = 1;
		else if (i != 0 && strcmp(token[i - 1]->content, "<<"))
			token[i]->need_expand = 1;
		else
			token[i]->need_expand = 0;
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	dollar_inside_quotes_alone(char *content)
{
	int	i;

	i = 1;
	while (content[i] && content[i + 1])
	{
		if (content[i] == '$' && content[i - 1] == '"' && content[i + 1] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	check_for_delimeter(t_node *tokens)
{
	t_node	*current;

	current = tokens;
	while (current && current->next)
	{
		if (!strcmp(current->content, "<<")
			&& (current->next->content[0] == '\''
				|| current->next->content[0] == '"')
			&& ((current->next->content[
						ft_strlen(current->next->content) - 1] == '\'')
				|| (current->next->content[
						ft_strlen(current->next->content) - 1] == '"')))
			current->next->delimeter_inside_quotes = 1;
		else
			current->next->delimeter_inside_quotes = 0;
		current = current->next;
	}
}

int	ft_is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while ((input[i] >= 9 && input[i] <= 13) || input[i] == ' ' )
			i++;
		if (input[i])
			return (0);
	}
	return (1);
}

int	check_edge_case(char *content)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (content[i])
	{
		if (content[i] == '"' && s_quote == 0)
			d_quote = !d_quote;
		if (content[i] == '\'' && d_quote == 0)
			s_quote = !s_quote;
		if (content[i] == '$' && !s_quote && !d_quote)
			return (1);
		i++;
	}
	return (0);
}

char	*pass_dollar(char *content)
{
	int		i;
	char	*new;

	new = c_malloc(ft_strlen(content), 1);
	i = 1;
	while (content[i])
	{
		new[i - 1] = content[i];
		i++;
	}
	new[i - 1] = '\0';
	return (new);
}
