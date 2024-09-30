/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 06:25:11 by asebrani          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/30 05:02:52 by asebrani         ###   ########.fr       */
=======
/*   Updated: 2024/09/29 21:23:34 by cbajji           ###   ########.fr       */
>>>>>>> 2895ddd58827979b40343654befb524a65a3adf0
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
<<<<<<< HEAD
		ret = execute_blts(final->tokens->content ,final, list,env);
		exit_status(1,ret);
		exit(ret);
=======
		execute_blts(final->tokens->content ,final, list,env);
		exit_status(1,list -> exit );
		c_malloc(0, 0);
		exit(list->exit);
>>>>>>> 2895ddd58827979b40343654befb524a65a3adf0
	}
	else
		{
 			i = excutefilepath(final,list,env);
			if (i == 2)
			{
				if (final->tokens->type == 1 || final->tokens->type == 2)
				{
					puts("here");
					exit_status(1,i);
					write(2,final->tokens->content,ft_strlenn(final->tokens->content));
					write(2,": No such file or directory\n",28);
					dup2(fd_in,0);
					close(fd_in);
					c_malloc(0, 0);
					exit(127);
				}
					dup2(fd_in,0);
					close(fd_in);
					exit_status(1,127);
					c_malloc(0, 0);
					exit(127);
			}
				exit_status(1,i);
				dup2(fd_in,0);
				close(fd_in);
				c_malloc(0, 0);
				exit(127);
		}
	return 0;
}

// int handle_pipe(t_line *final,char **env,env_vars *list)
// {
// 	int pid;
// 	int i = -1;
// 	int pipes_count;
// 	int fd[2];
// 	int ret = 0;
// 	int fd_in = dup(0);
// 	pipes_count = ft_listsize(final);
// 	if (pipes_count == 1 && check_builtin(final,list,env))
// 	{
// 			execute_blts(final->tokens->content,final,list,env);
// 			if(final->fd_in != 0)
// 			{
// 				dup2(final->default_in,0);
// 				close(final->fd_in);
// 			}
// 			if (final ->fd_out != 1)
// 			{
// 				dup2(final->default_out,1);
// 				close(final->fd_out);
// 			}
// 	}
// 	else
// 	{
// 		while (++i < pipes_count)
// 		{
// 			if (pipes_count > 1 && pipe(fd) == -1)
// 				return (fprintf(stderr,"error in pipes\n"),20);
// 			pid = fork();
// 			if (pid == -1)
// 				return (fprintf(stderr,"error in forking\n"),-1);
// 			if (pid == 0)
// 			{
// 				if (i != pipes_count - 1)
// 				{
// 					if (dup2(fd[1], 1) == -1)
// 						return(fprintf(stderr,"error in dup2"),-1);
// 					close(fd[0]);
// 				}
// 				handle_redirections(final);
// 				ret = execute_the_thing(final,env,list);
// 				if(final->fd_in != 0)
// 				{
// 					dup2(final->default_in,0);
// 					close(final->fd_in);
// 				}
// 				if (final ->fd_out != 1)
// 				{
// 					dup2(final->default_out,1);
// 					close(final->fd_out);
// 				}
// 				close(final->fd_in);
// 				close(final->fd_out);

// 			}
// 			else
// 			{
// 				if (pipes_count - 1 > 0)
// 				{
// 					if (dup2(fd[0],0))
// 						return(fprintf(stderr,"error in dup2"),-1);
// 					close(fd[1]); 
// 					close(fd[0]);
// 				}
// 			}
// 			final = final->next;
// 	}
// 	}
// 	while (pipes_count-- > 0)
// 		wait(NULL);
// 	dup2(fd_in,0);
// 	close(fd_in);
// 	return(ret);
// }
int handle_single_command(t_line *final, char **env, env_vars *list)
{
<<<<<<< HEAD
	int ret;
	
	ret = 0;
    ret = execute_blts(final->tokens->content, final, list, env);
    if (final->fd_in != 0)
    {
        dup2(final->default_in, 0);
        close(final->fd_in);
    }
    if (final->fd_out != 1)
    {
        dup2(final->default_out, 1);
        close(final->fd_out);
    }
    return ret;
}
int handle_multiple_commands(t_line *final, char **env, env_vars *list, int pipes_count)
{
    int pid;
    int i = -1;
    int fd[2];
    int ret = 0;
=======
	int pid;
	int i = -1;
	int pipes_count;
	int fd[2];
	int ret = 0;
	int fd_in = dup(0);
	pipes_count = ft_listsize(final);
	if (pipes_count == 1 && check_builtin(final,list,env))
	{
				fprintf(stderr, "\n\nin handle_pipe  blt = [%s]\n\n", final->tokens->content);

			execute_blts(final->tokens->content,final,list,env);
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
>>>>>>> 2895ddd58827979b40343654befb524a65a3adf0

    while (++i < pipes_count)
    {
        if (pipes_count > 1 && pipe(fd) == -1)
            return (write(2, "error in pipes\n",15), -1);
        pid = fork();
        if (pid == -1)
            return (write(2, "error in forking\n",17), -1);
        
        if (pid == 0)
        {
            ret = handle_child_process(final, env, list, i, pipes_count, fd);
			exit_status(1,ret);
            exit(ret);
        }
        else
			handle_parent_process(fd, pipes_count);
        final = final->next;
    }
    return (ret);
}

int handle_pipe(t_line *final, char **env, env_vars *list)
{
    int pipes_count;
    int ret = 0;
    int fd_in = dup(0);
	int status;

    pipes_count = ft_listsize(final);
    
    if (pipes_count == 1 && check_builtin(final, list, env))
        ret = handle_single_command(final, env, list);
    else
        ret = handle_multiple_commands(final, env, list, pipes_count);
    while (pipes_count-- > 0)
	{
		
        wait(&status);
		if (WEXITSTATUS(status))
			ret = WEXITSTATUS(status);
	}
	dup2(fd_in, 0);
    close(fd_in);
	exit_status(1, ret);
	//printf("%d\n",ret);
    return(ret);
}
