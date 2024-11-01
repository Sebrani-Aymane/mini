/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 06:25:11 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/01 18:23:13 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirections(t_line *final)
{
	open_files(final, final->tokens, 0, 0);
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
		exit(ret);
	}
	else
		when_not_blt(final, env, list);
	return (0);
}

int	handle_child_redirections(struct handle_attr *attr)
{
	if (attr->i != attr->pipes_count - 1)
	{
		if (dup2(attr->fd[1], 1) == -1)
			return (ft_putstr("error in dup2", 2), -1);
		if (close(attr->fd[0]) == -1)
			return (write(2, "something really bad\n", 21), -1);
	}
	return (0);
}

void	restore_file_descriptors(t_line *final)
{
	if (final->fd_in != 0)
	{
		dup2(final->fd_in, 0);
		close(final->fd_in);
	}
	if (final->fd_out != 1)
	{
		dup2(final->fd_out, 1);
		close(final->fd_out);
	}
}

int	child_process(struct handle_attr *attr, t_line *final,
				char **env, env_vars *list)
{
	if (attr->pid == 0)
	{
		signals_ignore();
		if (handle_child_redirections(attr) < 0)
			return (-1);
		handle_redirections(final);
		attr->ret = execute_the_thing(final, env, list);
		restore_file_descriptors(final);
		exit (1);
	}
	return (0);
}
