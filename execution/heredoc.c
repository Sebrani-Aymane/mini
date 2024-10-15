/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:55:44 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/15 19:55:58 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

void handle_heredoc(t_line *final, env_vars *list, char **env) {
	char *delim;
	char *input;
	char buffer[100];
	char namefile[21];
	int fd;
	(void)list;
	(void)env;
	//char last_input[10];
	int flag = 0;

	while (final) 
	{
		while (final->tokens)
		{
			if (final->tokens->type == 3)
			{
				int rand = open("/dev/urandom", O_RDWR);
				int j = 0;
				int i = 0;
				while (1)
				{
					read(rand, buffer, 100);
					buffer[99] = '\0';
					while (buffer[i])
					{
						if (ft_isalnum(buffer[i]))
						{
							namefile[j] = buffer[i];
							j++;
						}
						i++;
					}
					if (j == 20)
						break;
				}
				close(rand);
				namefile[19] = '\0';
				fd = open(namefile, O_RDWR | O_CREAT);
				delim = ft_strdup(final->tokens->next->content);
				while(1)
				{
					input = readline(">");
					if (!input || !ft_strcmp(input, delim))
				 		break;
					write(fd, input, ft_strlen(input));
					flag = 1;
				}
			}
			final->tokens = final->tokens->next;
			if (flag){
				dup2(fd,final->fd_in);
				close(fd);
			}
		}
		final = final->next;
	}
}
