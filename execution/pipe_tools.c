/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:32:50 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/30 21:32:32 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>


void chdiir_help(t_line *final,env_vars *list,char *pwd)
{
	t_node *token;
	env_vars *temp;

	token = final->tokens->next;
	temp = list;
	if (!ft_strcmp(token->content,".."))
	{
		while (temp)
		{
			if (!ft_strcmp(temp->vars,"OLDPWD") || !ft_strcmp(temp->vars,"PWD"))
			{
				if (!strcmp(temp->vars,"OLDPWD"))
				temp->var_value = strdup(pwd);
				else if (!strcmp(temp->vars,"PWD"))
					temp->var_value = str_joiner(get_path_from_list(list,"PWD"),"/..");
			}
			temp = temp ->next;
		}
	}
}

int handle_child_process(t_line *final, char **env, env_vars *list, int i, int pipes_count, int fd[2])
{
    if (i != pipes_count - 1)
    {
        if (dup2(fd[1], 1) == -1)
            return (fprintf(stderr, "error in dup2"), -1);
        close(fd[0]);
    }
    handle_redirections(final);
    puts("here1");
    int ret = execute_the_thing(final, env, list);
    if (final->fd_in != 0)
    {
        dup2(final->default_in, 0);
        close(final->fd_in);
    }
    if (final->fd_out != 1)
    {
        dup2(final->default_out, 1);
        close(final->fd_out);
    }
    close(final->fd_in);
    close(final->fd_out);
    return ret;
}

void handle_parent_process(int fd[2], int pipes_count)
{
    if (pipes_count - 1 > 0)
    {
        if (dup2(fd[0], 0) == -1)
            fprintf(stderr, "error in dup2");
        close(fd[1]);
        close(fd[0]);
    }
}