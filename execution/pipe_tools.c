/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:32:50 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/12 21:04:01 by cbajji           ###   ########.fr       */
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

int	setup_pipe(struct s_handle_attr *attr)
{
	if (attr->pipes_count > 1 && pipe(attr->fd) == -1)
		return (ft_putstr("error in pipes", 2), 20);
	return (0);
}

int	create_child_process(struct s_handle_attr *attr)
{
	attr->pid = fork();
	if (attr->pid == -1)
		return (ft_putstr("error in forking\n", 2), -1);
	return (0);
}

void	wait_for_children(struct s_handle_attr *attr)
{
	while (attr->pipes_count-- > 0)
	{
		waitpid(attr->pid, &attr->status, 0);
		handle_child_signals(attr->status);
	}
}

void	cleanup_pipe_handler(struct s_handle_attr *attr)
{
	dup2(attr->fd_in, 0);
	close(attr->fd_in);
	signals_allow();
}
