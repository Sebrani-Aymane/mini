/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:58:46 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/06 18:55:19 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_to_add(t_env_vars *env, char *str)
{
	char		*temp;
	t_env_vars	*tmp;
	t_env_vars	*new;
	char		*key;

	new = c_malloc(sizeof(t_env_vars), 1);
	if (!new)
		return (1);
	key = get_till(str, '=');
	tmp = env;
	temp = ft_strchrr(str, '=');
	if (!check_key(key))
		return (1);
	new -> vars = get_till(str, '=');
	new -> var_value = ft_strdup(temp + 1);
	add_to_list(&tmp, new);
	return (0);
}

int	export_it(t_env_vars *env, char *str)
{
	char	*key;
	char	*value;
	int		ret;

	value = ft_strchrr(str, '=');
	key = get_till(str, '=');
	while (env && env ->next)
	{
		if (ft_strncmp(env->vars, key, ft_strlenn(key)) == 0)
			return (env->var_value = ft_strdup(value + 1), 0);
		else if (ft_strncmp(env->next->vars, key, ft_strlenn(key)) == 0)
			return (env->next->var_value = ft_strdup(value + 1), 0);
		env = env->next;
	}
	ret = valid_to_add(env, str);
	return (ret);
}

int	export_all(t_env_vars *env, t_line *final)
{
	int		ret;
	t_node	*current;

	current = final->tokens->next;
	ret = 0;
	while (current)
	{
		if (ft_strchr(current->content, '+'))
			ret = export_with_plus(current->content, env);
		else if (!(ft_strchr(current->content, '=')))
			ret = first_in(current->content, env);
		else if (ft_strchr(current->content, '='))
			ret = export_it(env, current->content);
		current = current->next;
	}
	return (ret);
}
