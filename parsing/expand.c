#include "../minishell.h"

int can_expand(char *input)
{
    int d_quote = 0;
    int s_quote = 0; 
    int i = 0;

    while (input[i])
    {
        if (input[i] == '"')
            d_quote = !d_quote;

        if (input[i] == '\'' && d_quote == 0)
            s_quote = !s_quote; 

        if (input[i] == '$' && (d_quote || !s_quote))
            return (1);

        i++;
    }
    return (0);
}
int dollars_number(char *content, int need_exp)
{
    int i = 0;
    int counter = 0;
    if (can_expand(content) && need_exp)
    {
        while(content[i])
        {
            if (content[i] == '$')
                counter++;
            i++;
        }
    }
    return (counter);
}


char *variable_name(char *input)
{
    int start = 0;
    int i = 0;
    int len;
    
    while (input[i] && input[i] != '$')
        i++;
    start = i + 1;
    i++;
    while (input[i] && input[i] != ' ' && input[i] != '$')
        i++;
    if (input[0] == '"' && input[i] == '\0')
      len = i - start - 1;
    else
      len = i - start;
    char *var_name = malloc(sizeof(char) * (len + 1));
    if (var_name) {
        strncpy(var_name, input + start, len);
        var_name[len] = '\0';
    }
    return var_name;
}


char *get_value(char **env_vars, int len, char *name)
{
    int i = 0;
    int j = 0;
    char *value;
    while (env_vars[i])
    {
        if (strncmp(name, env_vars[i], len) == 0)
        {
            len++;
            break;
        }
        i++;
    }
    j = len;
    while (env_vars[i][j])
        j++;
    value = malloc(sizeof(char) * (j - len + 1));
    j = 0;
    while(env_vars[i][len])
    {
        value[j] = env_vars[i][len];
        j++;
        len++;
    }
    value[j] = '\0';
    return (value);

}

char *replace_value(char *token, char *value, char *name)
{
    int ignore_dollar;
    int name_len = strlen(name);
    int token_len = strlen(token);
    int value_len = strlen(value);
    int new_token_len;
    char *pos = strstr(token, name);
    if (!strcmp(name, "~"))
    {
        ignore_dollar = pos - token;
        new_token_len = (token_len - name_len) + value_len;
    }
    else 
    {
        ignore_dollar = (pos - token) - 1;
        new_token_len = (token_len - name_len - 1) + value_len;
    }
    char *new_token = malloc (sizeof(char) * new_token_len + 1);

    strncpy(new_token, token, ignore_dollar);
    new_token[ignore_dollar] = '\0';
    strcat(new_token, value);
    strcat(new_token, pos + name_len); 
    return (new_token);
}


void expand(t_token **tokens, t_list shell)
{
    int i = 0;
    char *name;
    int name_len;
    char *value;
    char *new_token;
    char *temp_token;
    int counter;

    check_token_dollar(shell.tokens);

    while (tokens[i])
    {
        counter = dollars_number(tokens[i]->content, tokens[i]->need_expand);
        if (counter == 0)
        {
            i++;
            continue;
        }
        temp_token = tokens[i]->content;
        while (counter)
        {
            
            name = variable_name(temp_token);
            name_len = strlen(name);
            value = get_value(shell.env_var, name_len, name);
            new_token = replace_value(temp_token, value, name);
            temp_token = new_token;
            counter--;
        }
        tokens[i]->content = new_token;
        i++;
    }
}
