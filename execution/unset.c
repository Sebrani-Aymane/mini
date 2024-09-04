/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:03:15 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/04 01:31:24 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void unset(env_vars *env, t_line *final)
{
    t_node *current = final->tokens->next;

    while (current)
    {
        env_vars *curr = env;
        env_vars *prev = NULL;

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
        current = current->next;
    }
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
        num = atoi(current->content);
    }
    else if (!current)
        exit(0);
    if (current->next)
    {
        printf("exit: too many arguments\n");
        return ;
    }
    exit(num);
}
