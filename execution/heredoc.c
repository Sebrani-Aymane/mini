/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:55:44 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/17 11:15:31 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
char *generate_filename(void)
{
	char *filename;
	int fd;
	int j;
	unsigned char c;

	j = 0;
	filename = malloc(21);
	if (!filename){
		perror("malloc");
	return(NULL);
	}
	fd = open("/dev/urandom",O_RDONLY);
	if (fd == -1){
		perror("open /dev/urandom");
	}
	while(j < 19)
	{
		if(read(fd,&c,1) == -1){
			perror("read /dev/urandom");
			close (fd);
			free(filename);
			return(NULL);
		}
		if(c <= 122 && c >=97)
	{		filename[j] = c;
		j++;
	}
	}
	filename[j] = '\0';
	close(fd);
	return(filename);
}

void handle_heredoc(t_line *final, env_vars *list, char **env) {
	char *delim;
	char *input;
	char *namefile;
	int fd = 0;

	(void)list;
	(void)env;
	int flag = 0;
	t_line *tmp;
	tmp = final;
	t_node *temp;
	temp = final->tokens;
	char *buff =ft_strdup("");
	while (final)
	{
		while (final->tokens)
		{
			if (final->tokens->type == 3)
			{
				namefile = generate_filename();
				fd = open(namefile, O_RDWR | O_CREAT | O_EXCL, 0600);
				if(!final->tokens->next)
					return;
				delim = ft_strdup(final->tokens->next->content);
				while(1)
				{
					input = readline(">");
					buff = ft_strjoin(buff,input);
					if (!input || !ft_strcmp(input, delim))
				 		return;
					write(fd, input, ft_strlen(input));
					write(fd,"\n",1);
					flag = 1;
				}
				final->tokens->content=namefile;
			close(fd);
			}
			final->tokens = final->tokens->next;
		}
		final = final->next;
	}
	final = tmp;
	final->tokens = temp;
}