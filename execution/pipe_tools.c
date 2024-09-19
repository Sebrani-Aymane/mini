/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:32:50 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/19 06:10:52 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_listsize(t_line *lst)
{
	int	i;
	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}


char *get_path_from_list(env_vars *list)
{
	char *path;
	
	while (list)
	{
		if(strcmp(list->vars,"PATH") == 0)
		{
			path = strdup(list->var_value);
			return(path);
		}
		list = list-> next;
	}
	return(NULL);
}
void chdiir_help(t_line *final,env_vars *list)
{
	t_node *token;
	env_vars *temp;
	char *curr_dir;

	token = final->tokens->next;
	curr_dir = getcwd(NULL,0);
	temp = list;
	if (!ft_strcmp(token->content,"..") || !ft_strcmp(token->content,".."))
	{
		while (temp)
		{
			if (!ft_strcmp(temp->vars,"OLDPWD") || !ft_strcmp(temp->vars,"PWD"))
			{
				if (!strcmp(temp->vars,"PWD") && !ft_strcmp(token->content,"..") )
					temp->var_value = str_joiner(curr_dir,"..");
				else if (!strcmp(temp->vars,"PWD") && !ft_strcmp(token->content,"."))
				temp->var_value = str_joiner(curr_dir,".");
			}
			temp = temp ->next;
		}
	}
}
