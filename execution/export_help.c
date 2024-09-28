/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:40:15 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/28 03:48:23 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_with_plus(char *str, env_vars *env)
{
	char	*key;
	char	*value;

	value = strchr(str, '=');
	key = get_till(str, '+');
	while (env && env->next)
	{
		if (ft_strcmp(env->vars, key) == 0)
		{
			break ;
			env->var_value = strdup(value);
		}
		env = env->next;
	}
	free (key);
	valid_to_add_plus(env, str);
}

void	first_in(char *str, env_vars *env)
{
	int			flag;
	env_vars	*new;

	flag = 0;
	if (!check_key(str))
		return ;
	new = malloc(sizeof(env_vars));
	if (!new)
		return ;
	while (env && env ->next)
	{
		if (ft_strcmp(env->vars, str) == 0
			|| ft_strcmp(env->next->vars, str) == 0)
			return (free(new));
		env = env->next;
	}
	if (!flag)
	{
		new->vars = strdup(str);
		new->var_value = strdup("");
		new->next = NULL;
		add_to_list(&env, new);
	}
}

void	valid_to_add_plus(env_vars *env, char *str)
{
	char		*temp;
	env_vars	*tmp;
	env_vars	*new;
	char		*key;

	key = get_till(str, '+');
	tmp = env;
	new = malloc(sizeof(env_vars));
	temp = strchr(str, '=');
	if (check_key(key))
	{
		if (strcmp(env->vars, key) == 0)
			env -> var_value = str_joiner(env->var_value, temp + 1);
		else
		{
			new-> vars = get_till(str, '+');
			new-> var_value = strdup(temp + 1);
			add_to_list(&tmp, new);
		}
		free(key);
	}
	else
		return;
}