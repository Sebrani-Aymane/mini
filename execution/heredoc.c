/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 01:27:29 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/25 23:13:52 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_herdoc(t_line *final)
{
	t_node	*temp;
	int		count;

	count = 0;
	while (final)
	{
		temp = final->tokens;
		while (temp)
		{
			if (temp->type == 3 && !ft_strncmp("<<", temp->content, 2))
				count++;
			temp = temp->next;
		}
		final = final->next;
	}
	return (count);
}

t_heredoc	*get_heredocs(t_line *final, int count)
{
	t_heredoc	*heredocs;
	int			i;

	heredocs = c_malloc((sizeof(t_heredoc) * count), 1);
	i = 0;
	while (final && i < count)
	{
		if (!get_delim_expand_pipe(final, heredocs, &i))
			return (NULL);
		final = final ->next;
	}
	return (heredocs);
}

void	process_heredoc(t_heredoc *heredoc, env_vars *list_env)
{
	char	*input;
	t_token	**hered_tokens;

	while (1)
	{
		input = readline(">");
		if (!input)
			return;
		if (ft_strncmp(input, heredoc->delimiter,
				ft_strlenn(heredoc->delimiter) == 0))
		{
			free(input);
			break ;
		}
		hered_tokens = into_tokens(input, 0, 0);
		writing_heredoc(hered_tokens, heredoc, list_env);
		write(heredoc->fd[1], "\n", 1);
		free(input);
	}
}

void	handle_heredoc(t_line *final, env_vars *list_env)
{
	t_heredoc	*heredocs;
	int			count;
	int			pid;
	int			i;

	i = 0;
	count = check_for_herdoc(final);
	if (count == 0)
		return ;
	heredocs = get_heredocs(final, count);
	if (!heredocs)
		return ;
	// signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_heredoc(heredocs, list_env, count);
	while (i < count)
		close(heredocs[i++].fd[1]);
	waitpid(pid, NULL, 0);
	signal(SIGINT, sigint_handler);
	if (final)
		final->fd_in = dup(heredocs[count - 1].fd[0]);
	i = 0;
	while (i < count)
		close(heredocs[i++].fd[0]);
}
