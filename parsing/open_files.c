/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:53:54 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/12 01:15:06 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

/*
word 1
built 2
heredoc 3
infile 4
outfile 5
append 6
*/

int	in_file(t_node *token)
{
	int	fd;

	fd = open(token->content, O_RDONLY);
	if ((!ft_strcmp(token->content, "") && token->need_expand == 1)
		|| token->content == NULL)
	{
		printf("minishell: %s: ambiguous redirect\n", token->content);
		return (0);
	}
	if (fd == -1)
	{
		ft_putstr("minishell:", 2);
		ft_putstr(token->content, 2);
		ft_putstr(": No such file or directory\n", 2);
		exit(1);
		return (0);
	}
	return (fd);
}

int	out_file(t_node *token)
{
	int	fd;

	fd = 1;
	if ((!ft_strcmp(token->content, "") && token->need_expand == 1)
		|| token->content == NULL)
	{
		printf("minishell: %s: ambiguous redirect\n", token->content);
		return (0);
	}
	if ((token->type == 5 && ft_strncmp(token->content, ">", 1))
		|| (token->type == 6 && token->inside_quotes))
		fd = open(token->content,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (((token->type == 6 && ft_strncmp(token->content, ">>", 2))
			|| (token->type == 6 && token->inside_quotes)))
		fd = open(token->content,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n",
			token->content);
		return (0);
	}
	return (fd);
}

int	handle_output(t_line *curr_line, t_node *curr_node, int out)
{
	if (curr_line->fd_out != 1)
		close(curr_line->fd_out);
	out = out_file(curr_node->next);
	curr_line->fd_out = out;
	return (out);
}

int	open_files(t_line *curr_line, t_node *curr_node, int in, int out)
{
	while (curr_line)
	{
		curr_node = curr_line->tokens;
		while (curr_node && curr_node->next)
		{
			if ((curr_node->type == 5 && curr_node->next->type == 5)
				|| (curr_node->type == 6 && curr_node->next->type == 6))
			{
				out = handle_output(curr_line, curr_node, out);
				if (!out)
					return (0);
			}
			else if (curr_node->type == 4 && curr_node->next->type == 4)
			{
				in = in_file(curr_node->next);
				if (!in)
					return (0);
				curr_line->fd_in = in;
			}
			curr_node = curr_node->next;
		}
		curr_line = curr_line->next;
	}
	return (1);
}
