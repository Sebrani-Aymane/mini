/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:32:50 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/11 01:12:42 by asebrani         ###   ########.fr       */
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

