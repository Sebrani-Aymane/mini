/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:32:50 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/29 23:20:05 by asebrani         ###   ########.fr       */
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

int	handle_child(t_line *final, char **env, env_vars *list,int *pipes_count)
{
	int	pid;
	int ret;
	int fd[2]
	if (pipes_count > 1 && pipe(fd) == -1)
		return (ft_putstr("error in pipes", 2), 20);
	pid = fork();
	if (pid == 0)
	{
		if (pid == 0)
		{
			signals_ignore();
			if (i != pipes_count - 1)
			{
				if (dup2(fd[1], 1) == -1)
					return (ft_putstr("error in dup2", 2), -1);
				if (close(fd[0]) == -1)
					write(2, "something really bad\n", 21);
			}
			handle_redirections(final);
			ret = execute_the_thing(final, env, list);
			close_files(final);
			exit(1);
		}
	}
}