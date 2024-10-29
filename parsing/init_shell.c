/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:10:58 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/29 20:17:22 by asebrani         ###   ########.fr       */
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
    int notif = 0;
    
    i = 0;
    while (env && env[i])
    {
        if (!strncmp(env[i], "SHLVL", 5))
        {
            temp = env[i];
            notif = 1;
            break;
        }
        i++;
    }
    if (notif)
    {
        while (temp && *temp != '=')
            temp++;
        temp++;
        shlvl = ft_atoi(temp) + 1;
        return (shlvl);
    }
    return (-1);
}

void set_shlvl(t_list shell)
{
    char *final;
    char *nbr;
    int i = 0;
    if (shell.shlvl != -1)
    {
        
    nbr = ft_itoa(shell.shlvl);
    final = ft_strjoin("SHLVL=", nbr);
    while(shell.env[i])
    {
        if (!strncmp(shell.env[i], "SHLVL", 5))
            shell.env[i] = final;
        i++;
    }
    }
}


void display_prompt(t_list shell, char **env, env_vars *list_env)
{
    char *input_rl;
    t_node *list;
    t_line *lines;
    struct termios  stats;
    char *input;
    if (tcgetattr(STDIN_FILENO, &stats) < 0)
            perror("terminal error ");
    while(1)
    {
        input_rl = readline("minishell-1.0$ ");
        if (glob_var)
            exit_status(1, 1);
        if (input_rl == NULL)
        {
            c_malloc(0, 0);
            rl_clear_history();
            printf("exit\n");
            exit(0);
        }
            
        if (strcmp(input_rl, ""))
            add_history(input_rl);
        if (ft_is_space(input_rl))
        {
            free(input_rl);
            continue;
        }
        glob_var = 0;
        input = calloc(sizeof(char), ((ft_strlenn(input_rl) - pass_spaces(input_rl)) + 2));
        copy_without_spaces(input, input_rl);
        if (ft_is_space(input) || (input[0] == ':' && !input[1]) || check_for_and(input))
        {
            free(input_rl);
            free(input);
            continue;
        }
        if (!strcmp(input, "''") || !strcmp(input, "\"\"") || check_unclosed_quotes(input, 0, 0, 0) || check_prohibited_char(input) || !validate_redirection_syntax(input) || !pipe_syntax(input, 0, 0))
        {
            if (!strcmp(input, "\"\"") || !strcmp(input, "''"))
                perror("minishell: : command not found\n");
            exit_status(1, 127);
            free(input);
            free(input_rl);
            continue; 
        }
        if (ft_strlenn(input) == 1 && input[0] != '/')
        {
            printf("minishell: %c:command not found\n", input[0]);
            exit_status(1, 127);
            free(input);
            free(input_rl);
            continue ; 
        }
        shell.tokens = into_tokens(input, 0, 0);
        // int i = 0;
        // while (shell.tokens[i])
        // {
        //     printf("token[%d]: %s\n", i, shell.tokens[i]->content);
        //     i++;
        // }
        free(input_rl);
        free(input);
  
        check_token_dollar(shell.tokens); 
        expand(shell.tokens, list_env); 

        expand_home(shell.tokens, list_env); 
  
        list = search_token(shell.tokens);
        // t_node *curr = list;
        // while(curr)
        //     {
        //         printf("token: %s\n", curr->content);
        //         curr = curr->next;
        //     }
        check_for_delimeter(list);

        lines = tokens_to_lines(list);
        // t_line *current = lines;
        // t_node *curr;
        // while(current)
        // {
        //     curr = current->tokens;
        //     printf("this is line:\n");
        //     while(curr)
        //     {
        //         printf("token: %s\n", curr->content);
        //         curr = curr->next;
        //     }
        //     current = current->next;
        //  }

        last_command(list_env, lines);
        handle_heredoc(lines, list_env);
        handle_pipe(lines,env,list_env);
        if(lines->fd_in)
            close(lines->fd_in);
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &stats) < 0)
            perror("terminal error ");
    }
}


// void display_prompt(t_list shell, char **env, env_vars *list_env)
// {
// char *input_rl;
//     t_node *list;
//     t_line *lines;
//     struct termios  stats;
//     char *input;
//     if (tcgetattr(STDIN_FILENO, &stats) < 0)
//             perror("terminal error ");
//     while(1)
//     {
//         input_rl = readline("minishell-1.0$ ");
//         if (glob_var)
//             exit_status(1, 1);
//         if (input_rl == NULL)
//         {
//             c_malloc(0, 0);
//             rl_clear_history();
//             printf("exit\n");
//             exit(0);
//         }
//         if (strcmp(input, ""))
//             add_history(input_rl);
            
//         if (ft_is_space(input_rl))
//         {
//             free(input_rl);
//             continue;
//         }
//         glob_var = 0;
//         input = malloc(sizeof(char) * ((ft_strlenn(input_rl) - pass_spaces(input_rl)) + 2));
//         copy_without_spaces(input, input_rl);
//         if (ft_is_space(input) || (input[0] == ':' && !input[1]) || check_for_and(input))
//         {
//             free(input_rl);
//             free(input);
//             continue;
//         }
//         if (!strcmp(input, "''") || !strcmp(input, "\"\"") || check_unclosed_quotes(input, 0, 0, 0) || check_prohibited_char(input) || !validate_redirection_syntax(input) || !pipe_syntax(input, 0, 0))
//         {
//             if (!strcmp(input, "\"\"") || !strcmp(input, "''"))
//                 printf("minishell: : command not found\n");
//             free(input);
//             free(input_rl);
//             continue; 
//         }
//         if (ft_strlenn(input) == 1 && input[0] != '/')
//         {
//             printf("minishell: %c:command not found\n", input[0]);
//             free(input);
//             free(input_rl);
//             continue ; 
//         }
//         shell.tokens = into_tokens(input, 0, 0);
//         free(input_rl);
//         free(input);
  
//         check_token_dollar(shell.tokens); 
//         expand(shell.tokens, list_env); 

//         expand_home(shell.tokens, list_env); 
  
//         list = search_token(shell.tokens);

//         check_for_delimeter(list);

//         lines = tokens_to_lines(list);

//         last_command(list_env, lines);
       
//         handle_heredoc(lines, list_env);
//         handle_pipe(lines,env,list_env);
//         if(lines->fd_in)
//             close(lines->fd_in);
//         if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &stats) < 0)
//             perror("terminal error ");
//     }
// }

