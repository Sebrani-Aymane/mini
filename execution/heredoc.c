/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 01:27:29 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/06 00:03:29 by cbajji           ###   ########.fr       */
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

void	process_heredoc(t_heredoc *heredoc, t_env_vars *list_env)
{
	char	*input;
	t_token	**hered_tokens;
	int		len;

	while (1)
	{
		input = readline(">");
		if (!input)
			return ;
			
		len = ft_strlenn(input);
		if (ft_strncmp(input, heredoc->delimiter,
				len) == 0 || (!ft_strcmp(input, "")))
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

void	handle_heredoc_parent(t_heredoc_params *params)
{
	int	i;
	int	status;

	i = 0;
	while (i < params->count)
		close(params->heredocs[i++].fd[1]);
	waitpid(params->pid, &status, 0);
	if (WEXITSTATUS(status) == 100)
		g_var = 100;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, params->stats) < 0)
		write(2, "Error restoring terminal attributes\n", 36);
	signal(SIGINT, sigint_handler);
	if (params->final)
		params->final->fd_in = dup(params->heredocs[params->count - 1].fd[0]);
	i = 0;
	while (i < params->count)
		close(params->heredocs[i++].fd[0]);
}

int	handle_heredoc(t_line *final, t_env_vars *list_env,
						struct termios *stats)
{
	t_heredoc_params	params;
	int i;

	i = 0;
	params.final = final;
	params.list_env = list_env;
	params.stats = stats;
	params.count = check_for_herdoc(final);
	if (params.count == 0)
		return ;
	params.heredocs = get_heredocs(final, params.count);
	if (!params.heredocs)
		return ;
	signal(SIGINT, SIG_IGN);
	params.pid = fork();
	if (params.pid == 0)
		child_heredoc(params.heredocs, params.list_env, params.count);
	else
		handle_heredoc_parent(&params);
	if (g_var == 100)
	{
		while (i < params.count)
    {
        if (close(params.heredocs[i].fd[0]) != -1 || 
            close(params.heredocs[i].fd[1]) != -1)
            i++; 
		return (0);
    }
	}
	return (1);
}
