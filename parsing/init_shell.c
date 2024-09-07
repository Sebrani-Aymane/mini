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

void display_prompt(t_list shell, char **env)
{
    char *input;
    t_node *list;
    (void)shell;
    t_line *lines;
    env_vars *liiiist;
    liiiist = list_init(env);
    while(1)
    {
        input = readline("minishell$  ");
        if (input == NULL)
        {
            printf("exit\n");
            exit(0);
        }
        else if (ft_strlen(input) == 0)
        {
            free(input);
            continue;
        }
        add_history(input);
        if (check_unclosed_quotes(input) || check_prohibited_char(input) || !validate_redirection_syntax(input) || !pipe_syntax(input))
            continue;
        shell.tokens = into_tokens(input);
        check_token_dollar(shell.tokens);
        expand(shell.tokens, shell);
        expand_home(shell.tokens, shell);
        list = search_token(shell.tokens);
        lines = tokens_to_lines(list);
        // open_files(lines);
        handle_pipe(lines,env,liiiist);
    }
}

