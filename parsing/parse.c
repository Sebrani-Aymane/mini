/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:20:30 by cbajji            #+#    #+#             */
/*   Updated: 2024/09/30 21:43:46 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
word 1
built 2
heredoc 3
infile 4
outfile 5
append 6
*/

char	*remove_quotes(char *content, int i, int j, char c)
{
	char	*final;

	final = c_malloc(sizeof(char) * ft_strlen(content) + 1, 1);
	if (!final)
		return (NULL);
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '\"')
		{
			c = content[i++];
			while (content[i])
			{
				if (content[i] != c)
					final[j++] = content[i];
				else if (content[i] == c)
					break ;
				i++;
			}
		}
		else
			final[j++] = content[i];
		i++;
	}
	final[j] = '\0';
	return (final);
}

void	final_tokens(t_node *token)
{
	t_node	*current;
	char	*final;

	current = token;
	while (current)
	{
		final = remove_quotes(current->content, 0, 0, 0);
		if (final)
		{
			free(current->content);
			current->content = final;
		}
		current = current->next;
	}
}

void	redirections_classifier(t_node **lst_token)
{
	t_node	*current;

	current = *lst_token;
	while (current)
	{
		if (current->type == 4 && !strcmp(current->content, "<")
			&& current->next != NULL && strcmp(current->next->content, ">"))
			current->next->type = 4;
		else if (current->type == 5 && (!strcmp(current->content, ">")
				|| !strcmp(current->content, ">>")) && current->next != NULL)
			current->next->type = 5;
		else if (current->type == 3 && (!strcmp(current->content, "<<"))
			&& current->next != NULL)
			current->next->type = 3;
			
		current = current->next;
	}
}

void	giving_type(t_node *token)
{
	t_node	*current;

	current = token;
	while (current)
	{
		if (!strcmp(current->content, "<"))
			current->type = 4;
		else if (!strcmp(current->content, ">")
			|| !strcmp(current->content, ">>"))
			current->type = 5;
		else if (!strcmp(current->content, "<<"))
			current->type = 3;
		else if (!strcmp(current->content, "echo")
			|| !strcmp(current->content, "cd")
			|| !strcmp(current->content, "pwd")
			|| !strcmp(current->content, "export")
			|| !strcmp(current->content, "unset")
			|| !strcmp(current->content, "env")
			|| !strcmp(current->content, "exit"))
			current->type = 2;
		else
			current->type = 1;
		current = current->next;
	}
}

void	add_n_l(t_node *curr, t_node **frst, t_node **last, t_line *line)
{
	t_node	*new_node;

	new_node = c_malloc(sizeof(t_node), 1);
	if (!new_node)
		return ;
	new_node->content = curr->content;
	new_node->type = curr->type;
	new_node->delimeter_inside_quotes = curr->delimeter_inside_quotes;
	new_node->next = NULL;
	if (!(*frst))
	{
		*frst = new_node;
		line->tokens = *frst;
	}
	else
		(*last)->next = new_node;
	*last = new_node;
}

t_line	*create_line(t_node *node)
{
	t_node	*current;
	t_node	*first;
	t_node	*last ;
	t_line	*line;

	current = node;
	first = NULL;
	last = NULL;
	line = c_malloc(sizeof(t_line), 1);
	if (!line)
		return (NULL);
	line->tokens = NULL;
	while (current && strcmp(current->content, "|") != 0)
	{
		add_n_l(current, &first, &last, line);
		current = current->next;
	}
	line->next = NULL;
	redirections_classifier(&line->tokens);
	line->fd_in = 0;
	line->fd_out = 1;
	return (line);
}

t_line	*tokens_to_lines(t_node *tokens)
{
	t_line	*first_line;
	t_line	*last_line;
	t_line	*line;

	first_line = NULL;
	last_line = NULL;
	giving_type(tokens);
	final_tokens(tokens);
	while (tokens)
	{
		line = create_line(tokens);
		if (!first_line)
			first_line = line;
		else
			last_line->next = line;
		last_line = line;
		while (tokens && strcmp(tokens->content, "|") != 0)
			tokens = tokens->next;
		if (tokens && strcmp(tokens->content, "|") == 0)
			tokens = tokens->next;
	}
	return (first_line);
}
