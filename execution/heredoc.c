/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:55:44 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/21 15:07:47 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int check_of_herdoc(t_line *final)
{
	t_node *temp;
	int count;
	
	count = 0;
	while (final)
	{
		temp = final->tokens;
		while (temp)
		{
			if (temp->type == 3 && !ft_strcmp("<< ",temp->content))
				count++;
			temp = temp->next;
		}
		final = final->next;
	}
	return (count);
}

t_node *get_delimiter(t_line *final)
{
		t_node *temp;
		temp = final->tokens;
		while (temp)
		{
			if (temp->type == 3)
			{	
				return (temp->next);
			}
			temp = temp->next;
		}
	return (NULL);
}

void handle_heredoc(t_line *final, env_vars *list_env)
{
	int fd[2];
	char *input;
	int pid;
	t_node *delimiter;
	t_token **hered_tokens;
	int i;
	int count;

	count = check_of_herdoc(final);
	if (count == 0)
		return;
	printf("%d\n",count);
	while (count -- != 0)
	{
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
				hered_tokens = into_tokens(input, 0, 0);
				if (delimiter->delimeter_inside_quotes != 1)
				{
					check_token_dollar(hered_tokens);
					expand(hered_tokens, list_env);
				}
				if (count - 1 == 0)
				{
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
		}
		exit_status(1, 0);
		c_malloc(0, 0);
		exit(0);
		}
		else
		{
			final->fd_in = dup(fd[0]);
			wait(NULL);
			close(fd[1]);
		}
	}
	return;
}
