/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:40:58 by cbajji            #+#    #+#             */
/*   Updated: 2024/09/20 18:19:48 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int can_expand_home(char *input)
{
    int i = 0;
    int d_quote = 0;
    int s_quote = 0;
    while (input[i])
    {
        if(input[i] == '"')
            d_quote = !d_quote;
        else if (input[i] == '\'')
            s_quote = !s_quote;
        if (input[i] == '~' && (s_quote || d_quote))
            return (0);
        i++;
    }
    return (1);
}


void expand_home(t_token **tokens, env_vars *list_env)
{
    int i = 0;
    char *value;
    char *new_token;
    while (tokens[i])
    {
        if (strchr(tokens[i]->content, '~'))
        {
            if(can_expand_home(tokens[i]->content))
            {
                value = get_value(list_env, 4, "HOME");
                new_token = replace_value(tokens[i]->content, value, "~");
                free(tokens[i]->content);
                tokens[i]->content = new_token;
            }
        }
        i++;
    }
}
