/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:22:57 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/01 21:42:03 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_delim_expand_pipe(t_line *final, t_heredoc	*heredocs, int	*i)
{
	t_node		*temp;

	temp = final->tokens;
	while (temp)
	{
		if (temp->type == 3
			&& !ft_strncmp("<<", temp->content, 2) && temp->next)
		{
			heredocs[*i].delimiter = ft_strdup(temp->next->content);
			heredocs[*i].expand_vars = !temp->next->delimeter_inside_quotes;
			if (pipe(heredocs[*i].fd) == -1)
			{
				while (--(*i) >= 0)
				{
					close(heredocs[*i].fd[0]);
					close(heredocs[*i].fd[1]);
				}
				return (0);
			}
			(*i)++;
		}
		temp = temp->next;
	}
	return (1);
}

void	writing_heredoc(t_token **hered_tokens,
						t_heredoc *heredoc, env_vars *list)
{
	int	j;

	j = 0;
	if (heredoc->expand_vars)
	{
		check_token_dollar(hered_tokens);
		expand(hered_tokens, list);
	}
	while (hered_tokens && hered_tokens[j])
	{
		write(heredoc->fd[1], hered_tokens[j]->content,
			ft_strlen(hered_tokens[j]->content));
		if (hered_tokens[j + 1])
			write(heredoc->fd[1], " ", 1);
		j++;
	}
}

void	child_heredoc(t_heredoc *heredocs, env_vars *list, int count)
{
	int	i;

	i = 0;
	signal(SIGINT, sigint_hand_heredoc);
	while (i < count)
		close(heredocs[i++].fd[0]);
	i = 0;
	while (i < count)
	{
		process_heredoc(&heredocs[i], list);
		if (glob_var)
			return ;
		close(heredocs[i].fd[1]);
		i++;
	}
	exit(0);
}
