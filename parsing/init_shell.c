#include "../minishell.h"

void print_token(t_node *token)
{
    printf("Token: %s, Type: %d\n", token->content, token->type);
}

// Function to print all tokens in a line
void print_line(t_line *line)
{
    t_node *current_token = line->tokens;
    printf("Line:\n");
    while (current_token)
    {
        print_token(current_token);
        current_token = current_token->next;
    }
    printf("\n");
}

// Function to print all lines
void print_lines(t_line *lines)
{
    t_line *current_line = lines;
    while (current_line)
    {
        print_line(current_line);
        current_line = current_line->next;
    }
}

char **copy_env(char **env)
{
    int size;
    char **to_copy;
    int i;

    i = 0;
    size = 0;
    while (env[size])
        size++;
    to_copy = malloc (sizeof(char *) * (size + 1));
    if (!to_copy)
    {
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

void display_prompt(t_list shell)
{
    char *input;
    t_node *list;
    env_vars *liiiist;

    t_line *lines;
    // int i = 0;
    while(1)
    {
        input = readline("minishell$  ");
        if (!input)
            exit(1);
        add_history(input);
        if (check_unclosed_quotes(input) || check_prohibited_char(input) || !validate_redirection_syntax(input))
            continue;
        shell.tokens = into_tokens(input);
        check_token_dollar(shell.tokens);
        expand(shell.tokens, shell);
        expand_home(shell.tokens, shell);
        list = search_token(shell.tokens);
        lines = tokens_to_lines(list);
        // t_line *copy = lines;
        print_lines(lines);
        liiiist = list_init(shell.env_var);
        execute_the_thing(&input,shell.env_var,liiiist);
        // while(copy)
        // {
        //     printf("%s\n", copy->tokens->content);
        //     copy = copy->next;
        // }
        // while(shell.tokens[i])
        // {
        //     printf("%s       %d\n", shell.tokens[i]->content, shell.tokens[i]->need_expand);
        //     i++;
        // }
    }
}
        // i = 0;
        
        // printf("%d\n", tokens_number(input));
