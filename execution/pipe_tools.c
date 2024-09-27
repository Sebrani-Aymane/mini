/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:32:50 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/27 14:25:23 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

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