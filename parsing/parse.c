/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:20:30 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/12 00:15:30 by cbajji           ###   ########.fr       */
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

void	redirections_classifier(t_node **lst_token)
{
	t_node	*current;

	current = *lst_token;
	while (current)
	{
		if (current->type == 4 && !ft_strcmp(current->content, "<")
			&& current->next != NULL && ft_strcmp(current->next->content, ">"))
			current->next->type = 4;
		else if (current->type == 5 && !ft_strcmp(current->content, ">")
			&& current->next != NULL)
			current->next->type = 5;
		else if (current->type == 3 && !ft_strcmp(current->content, "<<")
			&& current->next != NULL)
			current->next->type = 7;
		else if (current->type == 6 && !ft_strcmp(current->content, ">>")
			&& current->next != NULL)
			current->next->type = 6;
		current = current->next;
	}
}

void	giving_type(t_node *token)
{
	t_node	*cur;

	cur = token;
	while (cur)
	{
		if (!ft_strcmp(cur->content, "<") && !inside_quotes(cur->content))
			cur->type = 4;
		else if (!ft_strcmp(cur->content, ">") && !inside_quotes(cur->content))
			cur->type = 5;
		else if (!ft_strcmp(cur->content, ">>") && !inside_quotes(cur->content))
			cur->type = 6;
		else if (!ft_strcmp(cur->content, "<<") && !inside_quotes(cur->content))
			cur->type = 3;
		else if (!ft_strcmp(cur->content, "echo")
			|| !ft_strcmp(cur->content, "cd")
			|| !ft_strcmp(cur->content, "pwd")
			|| !ft_strcmp(cur->content, "export")
			|| !ft_strcmp(cur->content, "unset")
			|| !ft_strcmp(cur->content, "env")
			|| !ft_strcmp(cur->content, "exit"))
			cur->type = 2;
		else
			cur->type = 1;
		cur = cur->next;
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
	new_node->inside_quotes = curr->inside_quotes;
	new_node->need_expand = curr->need_expand;
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
	while (current && (ft_strcmp(current->content, "|") != 0
			|| current->inside_quotes))
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
	conf_inside_quotes(tokens);
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
		while (tokens && (ft_strcmp(tokens->content, "|") != 0
				|| tokens->inside_quotes))
			tokens = tokens->next;
		if (tokens && ft_strcmp(tokens->content, "|") == 0
			&& !tokens->inside_quotes)
			tokens = tokens->next;
	}
	return (first_line);
}
