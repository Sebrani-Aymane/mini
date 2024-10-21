/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:28 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/21 18:35:55 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

void	ft_putstr(char *s, int fd)
{
	write(fd, s, ft_strlenn(s));
}

void	echoo(t_line *final)
{
	int		newline;
	t_node	*current;
	t_node	*tmp;

	newline = 1;
	if (final->tokens->next)
	{
		current = final->tokens->next;
		tmp = current;
	}
	else
		current = NULL;
	if (check_eccho(current))
	{
		while (check_eccho(current))
			current = current->next;
		tmp = current;
		newline = 0;
	}
	current = tmp;
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
	char		*pwd;
	char		*temp;

	tmp = list;
	if (!list)
		return (NULL);
	pwd = getcwd(NULL, 0);
	temp = c_malloc(ft_strlenn(pwd) + 1, 1);
	copy_it(temp, pwd);
	free(pwd);
	if (!temp)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->vars, "PWD") == 0)
			{
				return (tmp->var_value);
			}
			tmp = tmp->next;
		}
	}
	return (temp);
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
	char		*home;
	int			res;
	char		*pwd_aftr_cd;
	char		*pwd_bfr_cd;
	env_vars	*temp;

	res = 0;
	pwd_bfr_cd = get_path_from_list(list, "PWD");
	if (!final->tokens->next)
	{
		home = get_path(env, "HOME=");
		if (!home)
			return (write(2, "minishell: cd: HOME not set\n", 28), 0);
		res = chdir(home);
	}
	else
	{
		res = chdir(final->tokens->next->content);
		pwd_aftr_cd = getcwd(NULL, 0);
		if (!pwd_aftr_cd)
		{
			if (!ft_strcmp(final->tokens->next->content,".."))
				chdiir_help(final, list, pwd_bfr_cd);
			else if (!ft_strcmp(final->tokens->next->content,".."))
				chdiir_help2(final, list, pwd_bfr_cd);
			return (res);
		}
	}
	temp = list;
	while (list)
	{
		if (!ft_strcmp(list->vars, "OLDPWD") || !ft_strcmp(list->vars, "PWD"))
		{
			if (strcmp(list->vars, "PWD"))
				list->var_value = pwd_bfr_cd;
			if (strcmp(list->vars, "OLDPWD"))
				list->var_value = getcwd(NULL, 0);
		}
		list = list ->next;
	}
	list = temp;
	return (res);
}
