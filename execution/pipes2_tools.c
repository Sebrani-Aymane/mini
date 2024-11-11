/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:19:46 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/11 22:44:38 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parent_process(struct s_handle_attr *attr)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (attr->pipes_count - 1 > 0)
	{
		if (dup2(attr->fd[0], 0) == -1)
			return (ft_putstr("error in dup2", 2), -1);
		close(attr->fd[1]);
		close(attr->fd[0]);
	}
	return (0);
}

void	handle_child_signals(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			printf("\n");
		else if (WTERMSIG(status) == SIGQUIT)
			printf("Quit: 3\n");
		exit_status(1, WTERMSIG(status) + 128);
	}
	if (WIFEXITED(status))
		exit_status(1, WEXITSTATUS(status));
}

void	init_pipe_attr(struct s_handle_attr *attr, t_line *final)
{
	attr->ret = 0;
	attr->fd_in = dup(0);
	attr->i = -1;
	attr->pipes_count = ft_listsize(final);
}

int	handle_single_builtin(struct s_handle_attr *attr, t_line *final,
							char **env, t_env_vars *list)
{
	if (attr->pipes_count == 1 && check_builtin(final, list, env))
	{
		attr->ret = handle_one_blt(final, env, list);
		exit_status(1, attr->ret);
		return (attr->ret);
	}
	return (-3);
}

int	handle_pipe(t_line *final, char **env, t_env_vars *list)
{
	struct s_handle_attr	attr;
	int						fork_ret;
	int						builtin_ret;
	int						pipe_ret;

	init_pipe_attr(&attr, final);
	builtin_ret = handle_single_builtin(&attr, final, env, list);
	if (builtin_ret != -3)
		return (cleanup_pipe_handler(&attr), builtin_ret);
	while (++attr.i < attr.pipes_count)
	{
		pipe_ret = setup_pipe(&attr);
		if (pipe_ret != 0)
			return (pipe_ret);
		fork_ret = create_child_process(&attr);
		if (fork_ret != 0)
			return (fork_ret);
		if (child_process(&attr, final, env, list))
			return (-1);
		else if (parent_process(&attr) != 0)
			return (-1);
		final = final->next;
	}
	wait_for_children(&attr);
	return (cleanup_pipe_handler(&attr), attr.ret);
}
