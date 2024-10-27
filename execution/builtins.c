/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:28 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/26 23:26:17 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echoo(t_line *final)
{
	t_node	*current;
	int		newline;

	check_echo_flags(final, &current, &newline);
	while (current)
	{
		if ((current->type == 1 || current->type == 2))
		{
			ft_putstr(current->content, 1);
			if (current->next)
				ft_putstr(" ", 1);
		}
		current = current->next;
	}
	if (newline)
		ft_putstr("\n", 1);
}

char	*pwdd(env_vars *list)
{
	env_vars	*tmp;

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

env_vars	*envpp(env_vars *list)
{
	env_vars	*tmp;

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
int	chdirr(char **env, t_line *final, env_vars *list)
{
	int			res;
	char		*pwd_bfr_cd;
	env_vars	*temp;

	pwd_bfr_cd = get_path_from_list(list, "PWD");
	res = cd_helper(final, list, env);
	if (res != 0)
		return (-1);
	temp = list;
	while (list)
	{
		if (!ft_strncmp(list->vars, "PWD", 3))
			list->var_value = getcwd(NULL, 0);
		if (!ft_strncmp(list->vars, "OLDPWD", 6))
			list->var_value = pwd_bfr_cd;
		list = list ->next;
		}
	list = temp;
	return (res);
	}

