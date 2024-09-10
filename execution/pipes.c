/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 06:25:11 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/10 22:51:15 by cbajji           ###   ########.fr       */
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
	int i =0;
	if (check_builtin(final, list, env)){
		execute_builtins(final->tokens->content ,final, list,env);
		exit(0); // exit with exit status
	}
	else
		{
 			i = excutefilepath(final,list,env);
	 		
			if (i == 2)
			{
				printf("minishell; %s: command not found\n",final->tokens->content);
				return(127);
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

	pipes_count = ft_listsize(final);
	if (pipes_count == 1 && check_builtin(final,list,env))
	{
			execute_builtins(final->tokens->content,final,list,env);
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
	}
	else
	{
		while (++i < pipes_count)
		{
			if (pipes_count > 1 && pipe(fd) == -1)
				return (printf("error in pipes\n"),20);
			pid = fork();
			if (pid == -1)
				return (printf("error in forking\n"),-1);
			if (pid == 0)
			{
				if (i != pipes_count - 1)
				{
					if (dup2(fd[1], 1) == -1)
						return(printf("error in dup2"),-1);
					close(fd[0]);
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
				close(final->fd_in);
				close(final->fd_out);
			}
			else
			{
				if (pipes_count - 1 > 0)
				{
					if (dup2(fd[0], 0))
						return(printf("error in dup2"),-1);
					puts("allo");
					close(fd[1]); 
					close(fd[0]);
				}
			}
			final = final->next;

	}
	}
	
	while (pipes_count-- > 0)
		wait(NULL);
	return(ret);
}