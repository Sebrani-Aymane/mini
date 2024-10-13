/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:55:44 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/13 12:05:06 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



 #include "../minishell.h"
#include <stdio.h>
 #include <stdio.h>
 #include <string.h>
#include <sys/fcntl.h>

int check_for_heredoc(t_line *final)
{
	t_node *temp;
	temp = final->tokens;
	while (final->tokens)
	{
		if (final->tokens->type == 3)
			return(1);
		final->tokens = final->tokens->next;
	}
	final->tokens = temp;
	return(0);
}

char *get_delimiters(t_line *final)
{
	char *ret;
	while (final->tokens)
	{
		if (final->tokens->type == 3)
			return(ft_strdup(final->tokens->next->content));
		final->tokens = final->tokens->next;
	}
}
void handle_herdoc(t_line *final, env_vars *list_env)
{
	int fd[2];
	int pid;
	char * delim;
	char *input;
	if (!check_for_heredoc(final))
		return;
	delim = get_delimiters(final);
	if (pipe(fd) == -1)
		return((void)write(2,"error in herdoc_ppipe\n",21));
	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		while(1)
		{
			input = readline(">");
			if (!input || !ft_strcmp(input,delim))
			{
				exit_status(1,0);
				exit(0);
			}
			write(fd[0],input,ft_strlenn(input)); 
			dup2(fd[0],final->fd_in);
			
			
		}
	}
}