/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:55:44 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/15 02:10:05 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include <stdio.h>
#include <string.h>
int check_of_herdoc(t_line *final)
{
	t_node *temp;
	while (final)
	{
		temp = final->tokens;
		while (temp)
		{
			if (temp->type == 3)
				return(1);
			temp = temp->next;
		}
		final = final->next;
	}
	return(0);
}
char *get_delimiter(t_line *final)
{
		char *ret = NULL;
		t_node *temp;
		temp = final->tokens;
		while (temp)
		{
			if (temp->type == 3)
			{
				ret = strdup(temp->next->content);	
				return(ret);
			}
			temp = temp->next;
		}
	return(NULL);
}
void handle_herdoc(t_line *final)
{
	int fd[2];
	char *input;
	int pid;
	char *delimiter;
	
	if (!check_of_herdoc(final))
		return;
	delimiter = get_delimiter(final);
	if (pipe(fd) == -1)
	{
		fprintf(stderr,"error with pipes in herdoc");
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			input = readline(">");
			if (!input)
				return(free(input));
			if (strcmp(input, delimiter) == 0)
				break;
			write(fd[1],input,ft_strlenn(input));
			write(fd[1],"\n",1);
			free(input);
		}
		close(fd[1]);
		exit(0);
	}
	else
	{
			close(fd[1]);
			wait(NULL);
	}
	final->fd_in = fd[0];
	return;
}























/*int	handle_redir_input_heredoc(char *delimiter, int *in_fd, int std_in)

function to handle here document input redirection
uses a pipe which acts as temporary storage for input
when the delimiter character is found, the whole input except the delimiter is redirected when in_fd is duplicated to open the write end of the pipe

*/