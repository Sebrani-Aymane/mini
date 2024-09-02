/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:58:46 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/02 17:56:10 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void valid_to_add(env_vars *env,char *str)
{
	char *temp;
	env_vars *tmp;
	env_vars *new;
	char *key;

	key = get_till(str,'=');
	tmp = env;
	new = malloc(sizeof(env_vars));
	temp = strchr(str, '=');
	if (check_key(key) && (temp + 1))
	{
		new-> vars = get_till(str,'=');
		new-> var_value = strdup(temp+1);
		add_to_list(&tmp,new);
		return;
	}
	else
		return;
}

void 	export_it(env_vars *env,char *str)
{
	char *key;
	char *value;

	value = strchr(str,'=');
	key = get_till(str,'=');
	while(env && env->next)
	{
		if (ft_strcmp(env->vars,key) == 0 || ft_strcmp(env->next->vars,key) == 0)
		{
			if (ft_strcmp(env->vars,key) == 0)
				env->var_value = strdup(value + 1);
			else if (ft_strcmp(env->next->vars,key) == 0)
				env->next->var_value= strdup(value + 1);
			return;
		}
		else
		env = env->next;
	}
	free(key);
	valid_to_add(env, str);
}

void export_all(env_vars *env, t_line *final)
{
	
	t_node *current = final->tokens->next;
	while (current)
	{
		if(strchr(current->content,'+'))
			export_with_plus(current->content,env);	
		else if (!(strchr(current->content,'=') ))
			first_in(current->content,env);
		else if (strchr(current->content,'='))
			export_it(env,current->content);
		current = current->next;
	}
}