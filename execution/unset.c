/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:03:15 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/08 15:40:58 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void unset(env_vars *env, t_line *final)
{
        t_node *current;
        env_vars *curr = env;
        env_vars *prev = NULL;

        if (final->tokens->next)
            current = final->tokens->next;
        else
         return;
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
                free(curr);
                break;
            }
            prev = curr;
            curr = curr->next;
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
        if (!ft_isalpha(curr->content[i]))
            return(255);
        i++;
    }
    return(0);
}
void exitt(env_vars *env, t_line *final)
{
    int num = 0;
    env_vars *temp;
    t_node *current = final->tokens->next;
    while(env)
    {
        temp = env->next;  
        free(env->vars);             
        free(env->var_value);        
        free(env);                   
        env = temp;
    }
    if (current)
    {
        if (!check_exit_stat(final))
        {
            printf("minishell$: exit: %s: numeric argument required",current->content);
            exit (255);
        }
        num = ft_atoi(current->content);
    }
    else if (!current)
        exit (0);
    if (current->next)
    {
        printf("minishell$: exit: too many arguments\n");
        return ;
    }
    exit(num);
}
int exit_status(int type, int value)
{
	static int var = 0;

	if (type == GET)
		return (var);
	else if (type == SET)
	{
		var = value;
		return var;
	}
	return var;
}