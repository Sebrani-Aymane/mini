/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:40:15 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/29 22:35:43 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_with_plus(char *str, env_vars *env)
{
	char	*key;
	char	*value;
	int ret;

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
	ret = valid_to_add_plus(env, str);
	return(ret);
}

int	first_in(char *str, env_vars *env)
{
	env_vars	*new;

	if (!check_key(str))
		return (1);
	new = malloc(sizeof(env_vars));
	if (!new)
		return (1);
	while (env && env ->next)
	{
		if (ft_strcmp(env->vars, str) == 0
			|| ft_strcmp(env->next->vars, str) == 0)
			return (free(new),0);
		env = env->next;
	}
	new->vars = strdup(str);
	new->var_value = strdup("");
	new->next = NULL;
	add_to_list(&env, new);
	return(0);
}

int	valid_to_add_plus(env_vars *env, char *str)
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
		return(0);
	}
	else
		return (1);
}