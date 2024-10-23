/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:55:44 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/23 00:18:21 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int check_for_herdoc(t_line *final)
{
	t_node *temp;
	int count;
	
	count = 0;
	while (final)
	{
		temp = final->tokens;
		while (temp)
		{
			if (temp->type == 3 && !ft_strcmp("<<",temp->content))
				count++;
			temp = temp->next;
		}
		final = final->next;
	}
	return (count);
}

t_heredoc *get_heredocs(t_line *final, int count)
{
    t_heredoc *heredocs;
    t_node *temp;
    int i;
    
    heredocs = c_malloc((sizeof(t_heredoc) * count),1);
    i = 0;
    while (final && i < count)
    {
        temp = final->tokens;
        while (temp)
        {
            if (temp->type == 3 && !ft_strcmp("<<", temp->content) && temp->next)
            {
                heredocs[i].delimiter = ft_strdup(temp->next->content);
                heredocs[i].expand_vars = !temp->next->delimeter_inside_quotes;
                if (pipe(heredocs[i].fd) == -1)
                {
                    while (--i >= 0)
                    {
                        free(heredocs[i].delimiter);
                        close(heredocs[i].fd[0]);
                        close(heredocs[i].fd[1]);
                    }
                    free(heredocs);
                    return (NULL);
                }
                i++;
            }
            temp = temp->next;
        }
        final = final->next;
    }
    return (heredocs);
}

void process_heredoc(t_heredoc *heredoc, env_vars *list_env)
{
    char *input;
    t_token **hered_tokens;
    int j;

    while (1)
    {
        input = readline(">");
        if (!input)
            exit(1);
        if (ft_strcmp(input, heredoc->delimiter) == 0)
        {
            free(input);
            break;
        }
        hered_tokens = into_tokens(input, 0, 0);
        if (heredoc->expand_vars)
        {
            check_token_dollar(hered_tokens);
            expand(hered_tokens, list_env);
        }
        j = 0;
        while (hered_tokens && hered_tokens[j])
        {
            write(heredoc->fd[1], hered_tokens[j]->content, 
                  strlen(hered_tokens[j]->content));
            if (hered_tokens[j + 1])
                write(heredoc->fd[1], " ", 1);
            j++;
        }
        write(heredoc->fd[1], "\n", 1);
        free(input);
    }
}

void handle_heredoc(t_line *final, env_vars *list_env)
{
    t_heredoc *heredocs;
    int count;
    int pid;
    int i;

    count = check_for_herdoc(final);
    if (count == 0)
        return;
    heredocs = get_heredocs(final, count);
    if (!heredocs)
        return;
    pid = fork();
    if (pid == 0)
    {
        i = 0;
        while (i < count)
        {
            close(heredocs[i].fd[0]);
            i++;
        }
        i = 0;
        while (i < count)
        {
            process_heredoc(&heredocs[i], list_env);
            close(heredocs[i].fd[1]);
            i++;
        }
        exit(0);
    }
    i = 0;
    while (i < count)
    {
        close(heredocs[i].fd[1]);
        i++;
    }
    waitpid(pid, NULL, 0);
    if (final)
        final->fd_in = dup(heredocs[count - 1].fd[0]);
    i = 0;
    while (i < count)
    {
        close(heredocs[i].fd[0]);
        free(heredocs[i].delimiter);
        i++;
    }
    free(heredocs);
}