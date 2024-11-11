/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deep_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:21:42 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/12 00:08:43 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_double_char_token(t_node **list, t_token *tokens, int *i)
{
	char	*token;

	token = c_malloc((sizeof(char) * 3), 1);
	if (!token)
		return ;
	token[0] = tokens->content[*i];
	token[1] = tokens->content[*i];
	token[2] = '\0';
	add_node(list, token, tokens->expanded);
	*i += 2;
}

void	add_single_char_token(t_node **list, t_token *tokens, int *i)
{
	char	*token;

	token = c_malloc((sizeof(char) * 2), 1);
	if (!token)
		return ;
	token[0] = tokens->content[*i];
	token[1] = '\0';
	add_node(list, token, tokens->expanded);
	(*i)++;
}

void	divide_and_add(t_node **list, t_token *token)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (token->content && token->content[i])
	{
		if (token->content[i] == '<' || token->content[i] == '>'
			|| token->content[i] == '|')
		{
			if (i > start)
				add_token(list, token, start, i);
			if (token->content[i + 1] == token->content[i])
				add_double_char_token(list, token, &i);
			else
				add_single_char_token(list, token, &i);
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		add_token(list, token, start, i);
}

void	divide_space(t_token *tok, t_node **list, int i, int start)
{
	int		end;
	char	*token;

	while (tok->content && (tok->content[i] == ' ' || tok->content[i] == '\t'))
		i++;
	start = i;
	while (tok->content && tok->content[i] != '\0')
	{
		if (tok->content[i] == ' ' || tok->content[i] == '\t')
		{
			end = i;
			token = cat_token(tok->content, start, end);
			add_node(list, token, tok->expanded);
			while (tok->content[i] == ' ' || tok->content[i] == '\t')
				i++;
			start = i;
		}
		else
			i++;
	}
	if (start < i)
	{
		token = cat_token(tok->content, start, i);
		add_node(list, token, tok->expanded);
	}
}

t_node	*search_token(t_token **tokens)
{
	int		i;
	t_node	*list;

	i = 0;
	list = NULL;
	while (tokens[i])
	{
		if (!contains_only_symbol(tokens[i]->content)
			&& contains_symbol(tokens[i]->content)
			&& !inside_quotes(tokens[i]->content)
			&& (i == 0 || ft_strcmp(tokens[i - 1]->content,
					"export") != 0))
			divide_and_add(&list, tokens[i]);
		else if (!inside_quotes(tokens[i]->content)
			&& tokens[i]->divide_space == 1)
			divide_space(tokens[i], &list, 0, 0);
		else
			add_node(&list, tokens[i]->content, tokens[i]->expanded);
		i++;
	}
	return (list);
}
