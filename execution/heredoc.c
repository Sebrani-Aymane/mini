/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:55:44 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/13 02:41:30 by asebrani         ###   ########.fr       */
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

char **get_delimiters(t_line *final)
{
    char **ret;
    char *delim;
    while (final)
    {
        while (final->tokens)
        {
            if(final->tokens->type == 3)
            {
                delim = ft_strjoin(final->tokens->next->content," ");
                final->tokens = final->tokens->next->next;
            }
			if (final->tokens && final->tokens->next)
            	final->tokens = final->tokens->next;
        }
        final = final->next;
    }
    ret = split(delim,' ');
    return(ret);
}
