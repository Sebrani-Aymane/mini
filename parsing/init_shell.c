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
        if (ft_strlen(input) == 0 || ft_is_space(input) || (input[0] == ':' && !input[1]) || check_for_and(input))
        {
            free(input);
            continue;
        }
        if (!strcmp(input, "\"\"") || check_unclosed_quotes(input) || check_prohibited_char(input) || !validate_redirection_syntax(input) || !pipe_syntax(input))
        {
            if (!strcmp(input, "\"\""))
                printf("minishell: : command not found\n");
            continue;
        }
        shell.tokens = into_tokens(input);
        check_token_dollar(shell.tokens);
        expand(shell.tokens, list_env);
        expand_home(shell.tokens, list_env);
        list = search_token(shell.tokens);
        check_for_delimeter(list);
        lines = tokens_to_lines(list);
        handle_herdoc(lines, list_env);
        handle_pipe(lines,env,list_env);
    }
}

