/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:10:58 by cbajji            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/04 05:26:00 by asebrani         ###   ########.fr       */
=======
/*   Updated: 2024/10/02 18:17:06 by cbajji           ###   ########.fr       */
>>>>>>> 4c1a846ae99dcd020b6ebf8e27f9ba90b9807f89
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
<<<<<<< HEAD
        //system("leaks minishell");
        input = readline("minishell$  "); 
=======
        // system("leaks minishell");
        input = readline("minishell$  ");
>>>>>>> 4c1a846ae99dcd020b6ebf8e27f9ba90b9807f89
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
        if (ft_strlenn(input) == 1)
        {
            printf("minishell: %c:command not found\n", input[0]);
            free(input);
            continue ; 
        }
        shell.tokens = into_tokens(input, 0, 0);
        free(input);
        check_token_dollar(shell.tokens); 
        expand(shell.tokens, list_env); 
        expand_home(shell.tokens, list_env); 
        list = search_token(shell.tokens);
        check_for_delimeter(list);
        lines = tokens_to_lines(list);
        last_command(list_env, lines); 
        handle_herdoc(lines, list_env);
        handle_pipe(lines,env,list_env);
    }
}

