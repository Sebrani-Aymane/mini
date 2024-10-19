/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:32:50 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/18 20:43:13 by asebrani         ###   ########.fr       */
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

int handle_one_blt(t_line *final,char **env,env_vars *list)
{
    int ret;
    handle_redirections(final);
    ret = execute_blts(final->tokens->content,final,list,env);
	if(final->fd_in != 0)
	{
		close(final->fd_in);
	    dup2(final->default_in,0);
	}
	if (final ->fd_out != 1)
	{
		close(final->fd_out);
		dup2(final->default_out,1);
	}
	close(final->default_in);
	close(final->default_out);
    return(ret);
}
