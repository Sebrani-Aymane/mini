/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:32:50 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/01 18:18:52 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_files(t_line *final)
{
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

int	setup_pipe(struct handle_attr *attr)
{
	if (attr->pipes_count > 1 && pipe(attr->fd) == -1)
		return (ft_putstr("error in pipes", 2), 20);
	return (0);
}

int	create_child_process(struct handle_attr *attr)
{
	attr->pid = fork();
	if (attr->pid == -1)
		return (ft_putstr("error in forking", 2), -1);
	return (0);
}

void	wait_for_children(struct handle_attr *attr)
{
	while (attr->pipes_count-- > 0)
	{
		wait(&attr->status);
		handle_child_signals(attr->status);
	}
}

void	cleanup_pipe_handler(struct handle_attr *attr)
{
	dup2(attr->fd_in, 0);
	close(attr->fd_in);
	signals_allow();
}
