/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 06:25:11 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/06 22:39:04 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/wait.h>
#include <unistd.h>

void handle_redirections(t_line *final)
{
    if(final->fd_in != 0)
	{
    	dup2(0,final->fd_in);
    	close(final->fd_in);
    	close(0);
	}
    if (final ->fd_out != 1)
	{        
		dup2(1,final->fd_out);
    	close(final->fd_out);
   		close(1);
    }    
	return;
}

void execute_the_thing(t_line *final,char **env,env_vars *list)
{
	char **builtins;
	int j=-1;
	char *str;
	int i;
	i = 1;
	
	str = get_path(env,"PATH=");
	builtins = split("cd echo pwd export unset env exit", ' ');
	while (builtins[++j])
	{
		if (strcmp(final->tokens->content,builtins[j]) == 0)
		{
			list = execute_builtins(builtins[j],final ,list,env);
			i = 0;
		}
	}
	free_double(builtins);
	if (i)
	{
		excutefilepath(final,str,env);
		i = 2;
	}
	else if (i == 2)
		printf("minishell; %s: command not found\n",final->tokens->content);
	return;
}

void handle_pipe(t_line *final,char **env,env_vars *list)
{
	int pid;
	int i = -1;
	int pipes_count;
	int fd[2];

	pipes_count = ft_listsize(final);
	int in_dup = dup(0);
	while (++i < pipes_count)
	{
			if (strcmp(final->tokens->content, "exit") == 0)
				exitt(list, final);
			if (pipes_count > 1 && pipe(fd) == -1)
				return ;
			pid = fork();
			if (pid == -1)
				return;
			if (pid == 0)
			{
				if (i != pipes_count - 1)
				{
					
					dup2(fd[1], 1);
					close(fd[1]);
					close(fd[0]);
				}
				handle_redirections(final);
				execute_the_thing(final,env,list);
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
	while (pipes_count-- > 0)
		wait(NULL);
	dup2(in_dup, 0);
	close(in_dup);
}
