/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 06:25:11 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/07 04:30:39 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include <sys/wait.h>
#include <unistd.h>

void handle_redirections(t_line *final)
{
	open_files(final);
    if(final->fd_in != 0)
	{
		final->default_in = dup(0);
    	dup2(final->fd_in,0);
	}
    if (final ->fd_out != 1)
	{
		final->default_out = dup(1);
		dup2(final->fd_out,1);
	}
	return;
}

int execute_the_thing(t_line *final,char **env,env_vars *list)
{
	int fd_in;
	int ret;

	fd_in = dup(0);
	int i =0;

	
	if (check_builtin(final, list, env))
	{
		ret = execute_blts(final->tokens->content ,final, list,env);
		exit_status(1,ret);
		c_malloc(0, 0);
		exit(ret);
	}
	else
	{
 		i = excutefilepath(final,list,env);
		if (i == 2)
		{
			if (final->tokens->type == 1 || final->tokens->type == 2)
			{
				exit_status(1,i);
				write(2,final->tokens->content,ft_strlenn(final->tokens->content));
				write(2,": No such file or directory\n",28);
				dup2(fd_in,0);
				close(fd_in);
				c_malloc(0, 0);
				exit(127);
			}
		}
	}
	return 0;
}

int handle_pipe(t_line *final,char **env,env_vars *list)
{
	int pid;
	int i = -1;
	int pipes_count;
	int fd[2];
	int ret = 0;
	int fd_in = dup(0);
	
	pipes_count = ft_listsize(final);
	// printf("%s\n",final->tokens->content);
	if (pipes_count == 1 && check_builtin(final,list,env))
		handle_one_blt(final,env,list);
	else
	{
		// printf("pipe count = %d\n", pipes_count);
		while (++i < pipes_count)
		{
			
			if (pipes_count > 1 && pipe(fd) == -1)
				return (fprintf(stderr,"error in pipes\n"),20);
			pid = fork();
			if (pid == -1)
				return (fprintf(stderr,"error in forking\n"),-1);
			if (pid == 0)
			{
				if (i != pipes_count - 1)
				{
					if (dup2(fd[1], 1) == -1)
						return(fprintf(stderr,"error in dup2"),-1);
					if (close(fd[0] == -1))
						write(1, "something really bad\n",21);
				}
				handle_redirections(final);
				ret = execute_the_thing(final,env,list);
				if(final->fd_in != 0)
				{
					dup2(final->default_in,0);
					close(final->fd_in);
				}
				if (final ->fd_out != 1)
				{
					dup2(final->default_out,1);
					close(final->fd_out);
				}
				 //close(final->fd_in);
				 //close(final->fd_out);
			}
			else
			{
				if (pipes_count - 1 > 0)
				{
					if (dup2(fd[0],0) == -1)
						return(fprintf(stderr,"error in dup2"),-1);
					close(fd[1]);
					close(fd[0]);
				}
			}
			final = final->next;
		}
	}
	while (pipes_count-- > 0)
		wait(NULL);
	dup2(fd_in,0);
	close(fd_in);
	return(ret);
}
