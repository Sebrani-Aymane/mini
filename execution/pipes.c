/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 06:25:11 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/08 19:53:27 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/wait.h>
#include <unistd.h>

void handle_redirections(t_line *final)
{
	open_files(final);
	printf("%d\n", final->fd_in );
	printf("%d\n", final->fd_out );
    if(final->fd_in != 0)
    	dup2(0,final->fd_in);
    if (final ->fd_out != 1)
		dup2(1,final->fd_out);    
	return;
}

int execute_the_thing(t_line *final,char **env,env_vars *list)
{
	int i =0;
	
 	i = excutefilepath(final,list,env);
	if (i == 2)
	{
		printf("minishell; %s: command not found\n",final->tokens->content);
		return(127);
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
	int in_dup = dup(0);

	pipes_count = ft_listsize(final);
	while (++i < pipes_count)
	{
		if (pipes_count > 1 && pipe(fd) == -1)
			return 10 ;
		handle_redirections(final);
		if (!check_builtin(final, list, env))
		{
		pid = fork();
		if (pid == -1)
			return -1;
		if (pid == 0)
		{
			if (i != pipes_count - 1)
			{	
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
				ret = execute_the_thing(final,env,list);
		}
		else
		{
			if (pipes_count - 1 > 0)
			{
				dup2(fd[0], 0);
				close(fd[1]);
				close(fd[0]);
			}
			final = final->next;
		}
		}
		else
			execute_builtins(final->tokens->content,final,list,env);
}
	while (pipes_count-- > 0)
		wait(NULL);
	dup2(in_dup, 0);
	close(in_dup);
	return(ret);
}