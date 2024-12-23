/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 01:27:29 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/11 21:51:27 by cbajji           ###   ########.fr       */
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

	while (1)
	{
		input = readline(">");
		if (!input)
			return ;
		if (ft_strcmp(input, heredoc->delimiter) == 0)
		{
			free(input);
			break ;
		}
		hered_tokens = into_tokens(input, 0, 0, 0);
		writing_heredoc(hered_tokens, heredoc, list_env);
		write(heredoc->fd[1], "\n", 1);
		free(input);
	}
}

void	handle_heredoc_parent(t_heredoc_params *params, int *sig_var)
{
	int	i;
	int	status;

	i = 0;
	while (i < params->count)
		close(params->heredocs[i++].fd[1]);
	waitpid(params->pid, &status, 0);
	if (WEXITSTATUS(status) == 100)
		*sig_var = 100;
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
	static int			sig_var;

	sig_var = 0;
	params.final = final;
	params.list_env = list_env;
	params.stats = stats;
	params.count = check_for_herdoc(final);
	if (params.count == 0)
		return (12);
	params.heredocs = get_heredocs(final, params.count);
	if (!params.heredocs)
		return (12);
	signal(SIGINT, SIG_IGN);
	params.pid = fork();
	if (params.pid == 0)
		child_heredoc(params.heredocs, params.list_env, params.count, &sig_var);
	else
	{
		handle_heredoc_parent(&params, &sig_var);
		if (sig_var == 100)
			return (0);
	}
	return (1);
}
