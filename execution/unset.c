/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:03:15 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/27 12:00:06 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void unset(env_vars *env, t_line *final)
{
		t_node *current;
		env_vars *curr;
		env_vars *prev = NULL;
		env_vars *env_bkp;

		if (!env)
			return;
		if (final->tokens->next)
			current = final->tokens->next;
		else
			return;
		env_bkp = env;
		// printf("this is currect %s\n", current->content);
		// printf("this is currect %s\n", current->next->content);
		// printf("this is currect %s\n", current->next->next->content);
		// printf("this is currect %p\n", current->next->next->next);
		while (current)
		{
			curr = env_bkp;
			while (curr)
			{
				if (ft_strcmp(curr->vars, current->content) == 0)
				{
					if (prev == NULL)
						env = curr->next; 
					else
						prev->next = curr->next;
					free(curr->vars);
					curr->vars = NULL;
					free(curr->var_value);
					curr->var_value = NULL;
					break;
				}
				prev = curr;
				curr = curr->next;
			}
			current = current->next;
		}
}
int check_exit_stat(t_line *final)
{
	t_node *curr = final->tokens->next;
	int i =0;

	if (!curr)
		return (0);
	while (curr ->content[i])
	{
		if (curr ->content[i] == '+' || curr ->content[i] == '-')
			i++;
		if(ft_isalpha(curr->content[i]))
			return(0);
		i++;
	}
	return(1);
}

void exitt(env_vars *env, t_line *final)
{
	int num = 0;
	env_vars *temp;
	t_node *current = final->tokens->next;
	if (current)
	{
		if (current->next && (check_exit_stat(final) || (ft_strlenn(current->content) < 19 && num < (int)9223372036854775807)))
		{
			printf("minishell$: exit: too many arguments\n");
			 exit_status(1,1);
			return;
		}
		num = ft_atoii(current->content);
		if (!check_exit_stat(final) || (ft_strlenn(current->content) > 19 && num > (int)9223372036854775807))
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",current->content);
			exit_status(1,255);
			exit(255);
		}
	}
	else
		exit(0);
	if (env && env->next)
	{
		while(env && env->next)
		{
			temp = env->next;
			free(env->vars);             
			free(env->var_value);        
			free(env);
			env = temp;
		}
	}
	exit_status(1,num);
	env ->exit = num;
	if (num > 255)
		exit(num % 255);
	exit(num);
}

int exit_status(int type, int value)
{
	static int var;

	if (type == GET)
		return (var);
	else if (type == SET)
	{
		var = value;
		return var;
	}
	return var;
}