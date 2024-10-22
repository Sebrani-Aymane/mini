/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:53:54 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/22 15:40:08 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	in_file(t_node *token)
{
	int fd;
	fd = open(token->content, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("minishell:",2);
		ft_putstr(token->content,2);
		ft_putstr(": No such file or directory\n", 2); 
		exit(1);
		return(0);
	}
	return (fd);
}

int	out_file(t_node *token)
{
	int fd;

	if (token->type == 5)
		fd = open(token->content,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
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

//TODO: close prev files
int	open_files(t_line *lines)
{
	t_line	*curr_line;
	t_node	*curr_node;
	int		in;
	int		out;

	curr_line = lines;
	while (curr_line)
	{
		curr_node = curr_line->tokens;
		while (curr_node && curr_node->next)
		{
			if (curr_node->type == 5 && curr_node->next->type == 5)
			{
				out = out_file(curr_node->next);
				lines->fd_out = out;
				if (!out)
					return 0 ;
			}
			else if (curr_node->type == 4 && curr_node->next->type == 4)
			{
				in = in_file(curr_node->next);
				if (!in)
					return 0;
				lines->fd_in = in;
			}
			curr_node = curr_node->next;
		}
		curr_line = curr_line->next;
	}
	return(1);		
}
