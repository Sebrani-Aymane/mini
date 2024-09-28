/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:10:58 by cbajji            #+#    #+#             */
/*   Updated: 2024/09/28 03:58:12 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **copy_env(char **env)
{
    int size;
    char **to_copy;
    int i;

    i = 0;
    size = 0;
    while (env[size])
        size++;
    to_copy = c_malloc ((sizeof(char *) * (size + 1)), 1);
    if (!to_copy)
    {
        c_malloc(0, 0);
        exit(1);
    }
    
    while (env[i])
    {
        to_copy[i] = strdup(env[i]);
        i++;
    }
    to_copy[i] = NULL;
    return (to_copy);
}

int get_shlvl(env_vars *list_env)
{
    int shlvl = 0;
    env_vars *temp = list_env;
    
    while (temp)
    {
        if (!strncmp(temp->vars, "SHLVL", 5))
        {
            shlvl = ft_atoi(temp->var_value);
            break;
        }
        temp = temp->next;
    }
    return (shlvl);
}

void set_shlvl(env_vars *list)
{
    env_vars *temp;

    temp = list;
    while (list)
    {
        if (strncmp(list->vars, "SHLVL=", 6) == 0)
        {
            free(list->var_value);
            list->var_value = strdup(ft_itoa(list->shlvl));
        }
        list = list->next;
    }
    list = temp;
}

void display_prompt(t_list shell, char **env, env_vars *list_env)
{
    char *input;
    t_node *list;
    t_line *lines;

    while(1)
    {
        input = readline("minishell$  ");
        add_history(input);
        if (input == NULL)
        {
            printf("exit\n");
            c_malloc(0, 0);
            exit(0);
        }
        if (ft_is_space(input) || (input[0] == ':' && !input[1]) || check_for_and(input))
        {
            free(input);
            continue;
        }
        if (ft_strlenn(input) == 1)
        {
            printf("minishell: %c:command not found\n", input[0]);
            free(input);
            continue ;
        }
        if (!strcmp(input, "\"\"") || check_unclosed_quotes(input, 0, 0, 0) || check_prohibited_char(input) || !validate_redirection_syntax(input) || !pipe_syntax(input, 0, 0))
        {
            if (!strcmp(input, "\"\""))
                printf("minishell: : command not found\n");
            continue;
        }
        shell.tokens = into_tokens(input, 0, 0);
        // int i = 0;
        // while(shell.tokens[i])
        // {
        //     printf("token[%d]: %s\n", i, shell.tokens[i]->content);
        //     i++;
        // }
        check_token_dollar(shell.tokens);
        expand(shell.tokens, list_env);
        expand_home(shell.tokens, list_env);
        list = search_token(shell.tokens);
        // t_node *current = list;
        // while(current)
        // {
        //     printf("token: %s\n", current->content);
        //     current = current->next;
        // }
        check_for_delimeter(list);
        lines = tokens_to_lines(list);
        // t_line *current = lines;
        // while (current)
        // {
        //     t_node *curr = current->tokens;
        //     printf("this is line: \n");
        //     while (curr)
        //     {
        //         printf("token: %s\n", curr->content);
        //         curr = curr->next;
        //     }
        //     current = current->next;
        // }
        handle_herdoc(lines, list_env);
        handle_pipe(lines,env,list_env);
    }
}

