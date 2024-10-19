/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:23:32 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/19 14:40:55 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_till(char *str, char c)
{
	int		size;
	char	*ret;
	int		i;

	i = 0;
	size = 0;
	while (str[size] && str[size] != c)
		size++;
	ret = c_malloc(sizeof(char) * (size + 1), 1);
	if (!ret)
		return (NULL);
	while (i < size)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	add_to_list(env_vars **head, env_vars *new)
{
	env_vars	*temp;

	temp = *head;
	if (!*head)
	{
		new -> next = NULL;
		*head = new;
	}
	else
	{
		while (temp && temp -> next)
			temp = temp -> next;
		temp->next = new;
		new->next = NULL;
	}
}

env_vars	*list_init(char **env)
{
	env_vars	*new;
	char		*temp;
	env_vars	*temp_var;

	new = NULL;
	while (*env)
	{
		temp_var = c_malloc((sizeof(env_vars)), 1);
		temp = strchr(*env, '=');
		if (!temp)
		{
			temp_var ->vars = ft_strdup(*env);
			temp_var -> var_value = NULL;
		}
		else
		{
			temp_var -> vars = get_till(*env, '=');
			temp_var -> var_value = ft_strdup(temp + 1);
		}
		add_to_list(&new, temp_var);
		env++;
	}
	return (new);
}

int	get_nodee(env_vars *list)
{
	while (list)
	{
		if (ft_strcmp(list->vars, "PATH") == 0)
			return (1);
		list = list->next;
	}
	return (0);
}
