/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:10:58 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/06 23:22:50 by asebrani         ###   ########.fr       */
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
    while (env && env[size])
        size++;
    to_copy = c_malloc ((sizeof(char *) * (size + 1)), 1);
    if (!to_copy)
    {
        c_malloc(0, 0);
        exit(1);
    }
    
    while (env[i])
    {
        to_copy[i] = ft_strdup(env[i]);
        i++;
    }
    to_copy[i] = NULL;
    return (to_copy);
}

int get_shlvl(char **env)
{
    int i;
    int shlvl;
    char *temp = NULL;
    
    i = 0;
    while (env && env[i])
    {
        if (!strncmp(env[i], "SHLVL", 5))
        {
            temp = env[i];
            break;
        }
        i++;
    }
    while (*temp != '=')
        temp++;
    temp++;
    shlvl = ft_atoi(temp) + 1;
    return (shlvl);
}

void set_shlvl(t_list shell)
{
    char *final;
    char *nbr;
    int i = 0;
    nbr = ft_itoa(shell.shlvl);
    final = ft_strjoin("SHLVL=", nbr);
    while(shell.env[i])
    {
        if (!strncmp(shell.env[i], "SHLVL", 5))
            shell.env[i] = final;
        i++;
    }
}

void display_prompt(t_list shell, char **env, env_vars *list_env)
{
    char *input;
    t_node *list;
    t_line *lines;
  //  int a = 0;
    while(1)
    {

        //system("leaks minishell");
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
        if (!strcmp(input, "''") || !strcmp(input, "\"\"") || check_unclosed_quotes(input, 0, 0, 0) || check_prohibited_char(input) || !validate_redirection_syntax(input) || !pipe_syntax(input, 0, 0))
        {
            if (!strcmp(input, "\"\"") || !strcmp(input, "''"))
                printf("minishell: : command not found\n");
            free(input);
            continue; 
        }
        if (ft_strlenn(input) == 1 && input[0] != '/')
        {
            printf("minishell: %c:command not found\n", input[0]);
            free(input);
            continue ; 
        }
        shell.tokens = into_tokens(input, 0, 0);
        // int i = 0;
        // while (shell.tokens[i])
        // {
        //     printf("%s\n",shell.tokens[i]->content);
        //     i++;
        // }
        free(input);
        check_token_dollar(shell.tokens); 
        expand(shell.tokens, list_env); 
        expand_home(shell.tokens, list_env); 
        list = search_token(shell.tokens);
        // t_node *curr = list;
        // while (curr)
        // {
        //     printf("%s\n", curr->content);
        //     curr = curr->next;
        // }
        check_for_delimeter(list);
        lines = tokens_to_lines(list);
        // t_line *current = lines;
        // while (current)
        // {
        //     t_node *curr = current->tokens;
        //     printf("this is line:\n");
        //     while (curr)
        //     {
        //         printf("this is token : %s\n", curr->content);
        //         curr = curr->next;
        //     }
        //     current = current->next;
        // }
        // last_command(list_env, lines);
        handle_herdoc(lines, list_env);
        handle_pipe(lines,env,list_env);
    }
}

