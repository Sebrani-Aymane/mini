/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:40:15 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/02 12:02:35 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_with_plus(char *str, t_env_vars *env)
{
	char	*key;
	char	*value;
	int		ret;

	value = ft_strchrr(str, '=');
	key = get_till(str, '+');
	while (env && env->next)
	{
		if (ft_strncmp(env->vars, key, ft_strlenn(key)) == 0)
		{
			break ;
			env->var_value = ft_strdup(value);
		}
		env = env->next;
	}
	ret = valid_to_add_plus(env, str);
	return (ret);
}

int	first_in(char *str, t_env_vars *env)
{
	t_env_vars	*new;

	if (!check_key(str))
		return (1);
	new = c_malloc(sizeof(t_env_vars), 1);
	if (!new)
		return (1);
	while (env && env ->next)
	{
		if (ft_strncmp(env->vars, str, ft_strlenn(str)) == 0
			|| ft_strncmp(env->next->vars, str, ft_strlenn(str)) == 0)
			return (0);
		env = env->next;
	}
	new->vars = ft_strdup(str);
	new->var_value = ft_strdup("");
	new->next = NULL;
	add_to_list(&env, new);
	return (0);
}

int	valid_to_add_plus(t_env_vars *env, char *str)
{
	char		*temp;
	t_env_vars	*tmp;
	t_env_vars	*new;
	char		*key;

	key = get_till(str, '+');
	tmp = env;
	new = c_malloc(sizeof(t_env_vars), 1);
	temp = ft_strchrr(str, '=');
	if (check_key(key))
	{
		if (ft_strncmp(env->vars, key, ft_strlenn(key)) == 0)
			env -> var_value = str_joiner(env->var_value, temp + 1);
		else
		{
			new -> vars = get_till(str, '+');
			new -> var_value = ft_strdup(temp + 1);
			add_to_list(&tmp, new);
		}
		return (0);
	}
	else
		return (1);
}
