/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deep_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:21:42 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/20 14:43:25 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inside_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	if ((str[0] == '"' || str[0] == '\'') && (str[len - 1] == '"'
			|| str[len - 1] == '\''))
		return (1);
	return (0);
}

int	contains_only_symbol(char *str)
{
	return (!strcmp(str, ">") || !strcmp(str, "<") || !strcmp(str, "<<")
		|| !strcmp(str, ">>") || !strcmp(str, "|"));
}

int	contains_symbol(char *str)
{
	return (ft_strchr(str, '>') || ft_strchr(str, '<') || ft_strchr(str, '|'));
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

void	add_double_char_token(t_node **list, char *content, int *i)
{
	char	*token;

	token = c_malloc((sizeof(char) * 3), 1);
	if (!token)
		return ;
	token[0] = content[*i];
	token[1] = content[*i];
	token[2] = '\0';
	add_node(list, token);
	*i += 2;
}

void	add_single_char_token(t_node **list, char *content, int *i)
{
	char	*token;

	token = c_malloc((sizeof(char) * 2), 1);
	if (!token)
		return ;
	token[0] = content[*i];
	token[1] = '\0';
	add_node(list, token);
	(*i)++;
}

void	divide_and_add(t_node **list, char *content)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (content && content[i])
	{
		if (content[i] == '<' || content[i] == '>' || content[i] == '|')
		{
			if (i > start)
				add_token(list, content, start, i);
			if (content[i + 1] == content[i])
				add_double_char_token(list, content, &i);
			else
				add_single_char_token(list, content, &i);
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		add_token(list, content, start, i);
}

void divide_space(char *content, t_node **list)
{
    int i = 0;
    int start, end;
    char *token;

    while (content && (content[i] == ' ' || content[i] == '\t'))
        i++;
    start = i;
    while (content && content[i] != '\0')
    {
        if (content[i] == ' ' || content[i] == '\t')
        {
            end = i;
            token = cat_token(content, start, end);
            add_node(list, token);
            while (content[i] == ' ' || content[i] == '\t')
                i++;
            start = i;
        }
        else
            i++;
    }

    if (start < i)
    {
        token = cat_token(content, start, i);
        add_node(list, token);
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
			&& !inside_quotes(tokens[i]->content))
			{
				printf("here in first cond\n");
			divide_and_add(&list, tokens[i]->content);
			}
		else if (!inside_quotes(tokens[i]->content) && tokens[i]->divide_space == 1)
		{
			printf("here in sec\n");
			divide_space(tokens[i]->content, &list);
		}
		else
		{
			printf("here in third\n");
			add_node(&list, tokens[i]->content);
		}
		i++;
	}
	return (list);
}
