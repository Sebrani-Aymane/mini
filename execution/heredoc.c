/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:55:44 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/15 17:38:57 by asebrani         ###   ########.fr       */
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
  char namefile[20];
  int fd;
  char last_input[10];

  while (final) {
    while (final->tokens) {
      if (final->tokens->type == 3)
	  {
        int rand = open("/dev/urandom", O_RDWR);
        int j = 0;
        int i = 0;
        while (1) {
          read(rand, buffer, 100);
          buffer[99] = '\0';
          while (buffer[i]) {
            if (ft_isalnum(buffer[i])) {
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
        	input = readline(">");
        	if (!input || ft_strcmp(input, delim))
         	 break;
        	write(fd, input, ft_strlen(input));
	}
      read(fd, last_input, 10) ;printf("%s\n", last_input);

      final->tokens = final->tokens->next;
    }
    final = final->next;
  }
}
