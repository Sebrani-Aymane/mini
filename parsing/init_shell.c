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
    shlvl = ft_atoi(temp);
    return (shlvl);
}
char **add_to_env(char **env, char *new_var)
{
    int i = 0;
    char **new_env;

    while (env[i])
        i++;

    new_env = c_malloc(sizeof(char *) * (i + 2), 1);
    
    for (i = 0; env[i]; i++)
        new_env[i] = env[i];
    new_env[i] = strdup(new_var);
    new_env[i + 1] = NULL;
    free(env);
    return new_env;
}


char **set_env(char **env, char *final)
{
     int i = 0;
    char **new_env;

    while (env[i] && strncmp(env[i], "SHLVL=", 6) != 0)
        i++;

    if (env[i])
    {
        free(env[i]);
        env[i] = strdup(final);
    }
    else
    {
        new_env = add_to_env(env, final);
        return (new_env);
    }
    return (env);
}

void set_shlvl(t_list shell)
{
    char *final;
    char *nbr;

    nbr = ft_itoa(shell.shlvl);
    final = ft_strjoin("SHLVL=", nbr);
    shell.env_var = set_env(shell.env_var, final);
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
            c_malloc(0, 0);
            exit(0);
        }
        if (ft_strlen(input) == 0)
        {
            free(input);
            continue;
        }

        add_history(input);
        if (!strcmp(input, "\"\"") || check_unclosed_quotes(input) || check_prohibited_char(input) || !validate_redirection_syntax(input) || !pipe_syntax(input))
        {
            if (!strcmp(input, "\"\""))
                printf("minishell: : command not found\n");
            continue;
        }
        shell.tokens = into_tokens(input);
        check_token_dollar(shell.tokens);
        expand(shell.tokens, shell);
        expand_home(shell.tokens, shell);
        list = search_token(shell.tokens);
        check_for_delimeter(list);
        lines = tokens_to_lines(list);
        handle_herdoc(lines, shell);
        handle_pipe(lines,env,liiiist);
    }
}

