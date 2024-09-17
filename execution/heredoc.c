/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:55:44 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/17 18:38:06 by cbajji           ###   ########.fr       */
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


t_node *get_delimiter(t_line *final)
{
		t_node *temp;
		temp = final->tokens;
		while (temp)
		{
			if (temp->type == 3)
			{	
				return(temp->next);
			}
			temp = temp->next;
		}
	return(NULL);
}
void handle_herdoc(t_line *final, t_list shell)
{
	int fd[2];
	char *input;
	int pid;
	t_node *delimiter;
	t_token **hered_tokens;
	int i;
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
			i = 0;
			input = readline(">");
			if (!input)
				return(free(input));
			hered_tokens = into_tokens(input);
			if (delimiter->delimeter_inside_quotes != 1)
			{
				check_token_dollar(hered_tokens);
				expand(hered_tokens, shell);
			}
			if (strcmp(input, delimiter->content) == 0)
				break;
			while (hered_tokens && hered_tokens[i])
			{
				write(fd[1], hered_tokens[i]->content, ft_strlenn(hered_tokens[i]->content));
				if (hered_tokens[i + 1])
					write(fd[1], " ", 1);
				i++;
			}
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