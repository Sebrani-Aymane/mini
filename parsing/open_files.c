/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:53:54 by cbajji            #+#    #+#             */
/*   Updated: 2024/09/11 00:26:10 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int in_file(t_line *line)
{
    t_node *current = line->tokens;
    while (current)
    {
        if (current->type == 4 && current->next->type == 4)
        {
            line->fd_in = open(current->next->content, O_RDONLY);
            if (line->fd_in == -1)
                return (0);
        }
        current = current->next;
    }
    return (1);
}

int out_file(t_line *line)
{
    t_node *current = line->tokens;
    while (current && current->next)
    {
        if (current->type == 5 && current->next->type == 5)
        {
            if (!strcmp(current->content, ">"))
                line->fd_out = open(current->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            else
                line->fd_out = open(current->next->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
            if (line->fd_out == -1)
                return (0);
        }
        current = current->next;
    }
    return (1);
}
//TODO: close prev files
void open_files(t_line *lines)
{
    t_line *current = lines;
    int in;
    int out;
    while (current)
    {
        in = in_file(current);
        out = out_file(current);
        
        if (!in || !out)
        {
            printf("Error in opening the file\n");
            return ;
        }
        current = current->next;
    }
}
