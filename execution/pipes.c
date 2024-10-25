/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 06:25:11 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/25 22:59:09 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirections(t_line *final)
{
	open_files(final);
	if (final->fd_in != 0)
	{
		dup2(final->fd_in, 0);
		close(final->fd_in);
	}
	if (final ->fd_out != 1)
	{
		dup2(final->fd_out, 1);
		close(final->fd_out);
	}
	return ;
}

int	execute_the_thing(t_line *final, char **env, env_vars *list)
{
	int	ret;
	int	i;

	i = 0;
	if (check_builtin(final, list, env))
	{
		ret = execute_blts(final->tokens->content,
				final, list, env);
		exit_status(1, ret);
		c_malloc(0, 0);
		exit(ret);
	}
	else
		when_not_blt(final, env, list);
	return (0);
}

void	signals_ignore()
{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
}

void	signals_allow(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	handle_pipe(t_line *final, char **env, env_vars *list)
{
	int	pid;
	int	i;
	int	pipes_count;
	int	fd[2];
	int	ret;
	int	fd_in;
	int	status;

	ret = 0;
	fd_in = dup(0);
	i = -1;
	pipes_count = ft_listsize(final);
	if (pipes_count == 1 && check_builtin(final, list, env))
	{
		ret = handle_one_blt(final, env, list);
		exit_status(1, ret);
	}
	else
	{
		while (++i < pipes_count)
		{
			if (pipes_count > 1 && pipe(fd) == -1)
				return (ft_putstr("error in pipes", 1), 20);
			pid = fork();
			if (pid == -1)
				return (ft_putstr("error in forking", 1), -1);
			signal(SIGINT, SIG_IGN);
			if (pid == 0)
			{
				signals_ignore();
				if (i != pipes_count - 1)
				{
					if (dup2(fd[1], 1) == -1)
						return (ft_putstr("error in dup2", 1), -1);
					if (close(fd[0]) == -1)
						write(1, "something really bad\n", 21);
				}
				handle_redirections(final);
				ret = execute_the_thing(final, env, list);
				if (final->fd_in != 0)
				{
					dup2(final->fd_in, 0);
					close(final->fd_in);
				}
				if (final ->fd_out != 1)
				{
					dup2(final->fd_out, 1);
					close(final->fd_out);
				}
			}
			else
			{
				signals_allow();
				if (pipes_count - 1 > 0)
				{
					if (dup2(fd[0], 0) == -1)
						return (ft_putstr("error in dup2", 1), -1);
					close(fd[1]);
					close(fd[0]);
				}
			}
			final = final->next;
		}
	}
	while (pipes_count-- > 0)
		wait(&status);
	if (WIFEXITED(status))
		exit_status(1, WEXITSTATUS(status));
	dup2(fd_in, 0);
	close(fd_in);
	return (ret);
}
