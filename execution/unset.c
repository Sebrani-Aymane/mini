/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:03:15 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/23 17:50:23 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void unset(env_vars *env, t_line *final)
{
        t_node *current;
        env_vars *curr;
        env_vars *prev = NULL;

        if (final->tokens->next)
            current = final->tokens->next;
        else
            return;
        while (current)
        {
            if (!env)
                return;
            curr = env;
            while (curr)
            {
                if (ft_strcmp(curr->vars, current->content) == 0)
                {
                    if (prev == NULL)
                        env = curr->next; 
                    else
                        prev->next = curr->next;
                    free(curr->vars);
                    free(curr->var_value);
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
    
    if (env)
    {
    while(env)
    {
        temp = env->next;  
        free(env->vars);             
        free(env->var_value);        
        free(env);                   
        env = temp;
    }
    }
    if (current)
    {
        if (!check_exit_stat(final))
        {
            printf("exit\nminishell: exit: %s: numeric argument required",current->content);
            exit_status(1,255);
            exit(255);
        }
        num = ft_atoii(current->content);
    }
    else
        exit(0);
    if (current->next)
    {
        printf("minishell$: exit: too many arguments\n");
        return;
    }
    exit_status(1,num);
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