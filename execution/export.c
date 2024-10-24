/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:58:46 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/23 22:09:19 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_to_add(env_vars *env, char *str)
{
	char		*temp;
	env_vars	*tmp;
	env_vars	*new;
	char		*key;

	new = c_malloc(sizeof(env_vars), 1);
	if (!new)
		return (1);
	key = get_till(str, '=');
	tmp = env;
	temp = strchr(str, '=');
	if (!check_key(key))
		return (1);
	new -> vars = get_till(str, '=');
	new -> var_value = ft_strdup(temp + 1);
	add_to_list(&tmp, new);
	return (0);
}

int	export_it(env_vars *env, char *str)
{
	char	*key;
	char	*value;
	int		ret;

	value = strchr(str, '=');
	key = get_till(str, '=');
	while (env && env ->next)
	{
		if (ft_strcmp(env->vars, key) == 0
			|| ft_strcmp(env->next->vars, key) == 0)
		{
			if (ft_strcmp(env->vars, key) == 0)
				env->var_value = ft_strdup(value + 1);
			else if (ft_strcmp(env->next->vars, key) == 0)
				env->next->var_value = ft_strdup(value + 1);
			return (0);
		}
		else
			env = env->next;
	}
	ret = valid_to_add(env, str);
	return (ret);
}

int	export_all(env_vars *env, t_line *final)
{
	int		ret;
	t_node	*current;

	current = final->tokens->next;
	ret = 0;
	while (current)
	{
		if (strchr(current->content, '+'))
			ret = export_with_plus(current->content, env);
		else if (!(ft_strchr(current->content, '=')))
			ret = first_in(current->content, env);
		else if (strchr(current->content, '='))
			ret = export_it(env, current->content);
		current = current->next;
	}
	return (ret);
}
