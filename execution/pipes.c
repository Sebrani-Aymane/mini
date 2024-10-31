/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 06:25:11 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/31 16:25:19 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/wait.h>
// #include <csignal>
// #include <signal.h>
// #include <sys/signal.h>

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

void	signals_ignore(void)
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
		return (ret);
	}
	else
	{
		while (++i < pipes_count)
		{
			if (pipes_count > 1 && pipe(fd) == -1)
				return (ft_putstr("error in pipes", 2), 20);
			pid = fork();
			if (pid == -1)
				return (ft_putstr("error in foking", 2), -1);
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
				exit(1);
			}
			else
			{
				signal(SIGINT, SIG_IGN);
				signal(SIGQUIT, SIG_IGN);
				if (pipes_count - 1 > 0)
				{
					if (dup2(fd[0], 0) == -1)
						return (ft_putstr("error in dup2", 2), -1);
					close(fd[1]);
					close(fd[0]);
				}
			}
			final = final->next;
		}
	}
	while (pipes_count-- > 0)
	{
		wait(&status);
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
	dup2(fd_in, 0);
	close(fd_in);
	signals_allow();
	return (ret);
}
// Main pipe handler

// void wait_and_handle_status(int pipes_count, int *status)
// {
//     while (pipes_count-- > 0)
//         wait(status);

//     signals_allow();
//     if (WIFSIGNALED(*status))
//     {
//         if (WTERMSIG(*status) == SIGINT)
//             printf("\n");
//         else if (WTERMSIG(*status) == SIGQUIT)
//             printf("Quit: 3\n");
//         exit_status(1, WTERMSIG(*status) + 128);
//     }
//     else if (WIFEXITED(*status))
// 		exit_status(1, WEXITSTATUS(*status));
// }

// int handle_multiple_pipes(t_line *final, char **env, env_vars *list, int pipes_count)
// {
//     int i;
//     int ret;

//     i = -1;
//     ret = 0;
//     while (++i < pipes_count)
//     {
//         ret = handle_single_pipe(final, env, list, pipes_count, i);
//         if (ret < 0)
//             return (ret);
//         final = final->next;
//     }
//     return (ret);
// }
// int handle_parent_process(int fd[2], int pipes_count)
// {
//     signal(SIGINT, SIG_IGN);
//     signal(SIGQUIT, SIG_IGN);
    
//     if (pipes_count - 1 > 0)
//     {
//         if (dup2(fd[0], 0) == -1)
//             return (ft_putstr("error in dup2", 1), -1);
//         close(fd[1]);
//         close(fd[0]);
//     }
//     return (0);
// }
// int handle_single_pipe(t_line *final, char **env, env_vars *list, 
//                       int pipes_count, int i)
// {
//     int pid;
//     int fd[2];

//     if (pipes_count > 1 && pipe(fd) == -1)
//         return (ft_putstr("error in pipes", 1), 20);
    
//     pid = fork();
//     if (pid == -1)
//         return (ft_putstr("error in forking", 1), -1);
    
//     signal(SIGINT, SIG_IGN);
//     if (pid == 0)
//         return (handle_child_processs(final, env, list, fd, pipes_count, i));
//     else
//         return (handle_parent_process(fd, pipes_count));
// }

// int handle_child_processs(t_line *final, char **env, env_vars *list, 
//                         int fd[2], int pipes_count, int i)
// {
//     int ret;

//     signals_ignore();
//     if (i != pipes_count - 1)
//     {
//         if (dup2(fd[1], 1) == -1)
//             return (ft_putstr("error in dup2", 1), -1);
//         if (close(fd[0]) == -1)
//             write(1, "something really bad\n", 21);
//     }
//     handle_redirections(final);
//     ret = execute_the_thing(final, env, list);
//     handle_child_fds(final);
//     exit(1);
// }



// void handle_child_fds(t_line *final)
// {
//     if (final->fd_in != 0)
//     {
//         dup2(final->fd_in, 0);
//         close(final->fd_in);
//     }
//     if (final->fd_out != 1)
//     {
//         dup2(final->fd_out, 1);
//         close(final->fd_out);
//     }
// }

// int handle_pipe(t_line *final, char **env, env_vars *list)
// {
//     int pipes_count;
//     int ret;
//     int fd_in;
//     int status;

//     ret = 0;
//     fd_in = dup(0);
//     pipes_count = ft_listsize(final);
//     if (pipes_count == 1 && check_builtin(final, list, env))
//     {
//         ret = handle_one_blt(final, env, list);
//         exit_status(1, ret);
//     }
//     else
//         ret = handle_multiple_pipes(final, env, list, pipes_count);
    
//     wait_and_handle_status(pipes_count, &status);
//     dup2(fd_in, 0);
//     close(fd_in);
//     return (ret);

//         exit_status(1, WEXITSTATUS(status));
// }
