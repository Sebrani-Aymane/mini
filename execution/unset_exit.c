/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:03:15 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/01 16:32:09 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void unset(env_vars *env, char **av)
{
    int i = 1;

    while (av[i])
    {
        env_vars *curr = env;
        env_vars *prev = NULL;

        while (curr)
        {
            if (ft_strcmp(curr->vars, av[i]) == 0)
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
        i++;
    }
}
