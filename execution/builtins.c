/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:28 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/07 20:46:02 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echoo(t_node *node)
{
	int		newline;

	check_echo_flags(&node, &newline);
	if (node)
	{
		while (node)
		{
			if ((node->type == 1 || node->type == 2))
			{
				ft_putstr(node->content, 1);
				if (node->next)
					ft_putstr(" ", 1);
			}
			node = node->next;
		}
	}
	if (newline)
		ft_putstr("\n", 1);
	exit_status(1, 0);
}

char	*pwdd(t_env_vars *list)
{
	t_env_vars	*tmp;

	tmp = list;
	if (!list)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->vars, "PWD", 3) == 0)
			return (tmp->var_value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env_vars	*envpp(t_env_vars *list)
{
	t_env_vars	*tmp;

	tmp = list;
	if (!list)
		return (NULL);
	while (list)
	{
		if (list->vars)
			printf("%s", list->vars);
		if (list->var_value && *(list->var_value) != '\0')
			printf("=%s\n", list->var_value);
		else
			printf("\n");
		list = list->next;
	}
	return (tmp);
}

int	chdirr(char **env, t_line *final, t_env_vars *list)
{
	t_env_vars	*temp;
	char		*str;
	char		*oldpwd;

	oldpwd = get_path_from_list(list, "PWD");
	if (cd_helper(final, list, env) != 0)
		return (-1);
	temp = list;
	str = getcwd(NULL, 0);
	if (!str)
		str = get_path_from_list(list, "PWD");
	while (list)
	{
		if (!ft_strncmp(list->vars, "PWD", 3))
		{
			list->var_value = ft_strdup(str);
			list->pwd = ft_strdup(list->var_value);
		}
		if (!ft_strncmp(list->vars, "OLDPWD", 6))
			list->var_value = oldpwd;
		list = list ->next;
	}
	if (str)
		free(str);
	return ((list = temp), 0);
}
