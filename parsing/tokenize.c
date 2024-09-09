#include "../minishell.h"

int tokens_number(char *input)
{
    int i = 0;
    int notif = 1;
    int count = 0;
    int end = 0;

    while (input[i] == ' ' || input[i] == '\t')
        i++;
    end = i;
    while (input[end])
        end++;
    while (end > 0 && (input[end - 1] == ' ' || input[end - 1] == '\t'))
        end--;
    if (i == end)
        return 0;

    while (i < end)
    {
        if (input[i] == '\'' || input[i] == '"')
            notif = -notif;
        else if ((input[i] == ' ' || input[i] == '\t') && notif > 0)
        {
            count++;
            while ((input[i] == ' ' || input[i] == '\t') && notif > 0)
                i++;
            i--;
        }
        i++;
    }
    return count + 1;
}

int divide(char *input, int start)
{
    int i;
    int end;
    int notif;
    int last;

    i = 0;
    notif = 1;
    while (start == 0 && (input[i] == ' ' || input[i] == '\t'))
        i++;
    last = start;
    while (input[last])
        last++;
    while (last > 0 && (input[last - 1] == ' ' || input[last - 1] == '\t'))
        last--;
    while (start < last)
    {
        if(input[start] == '\'' || input[start] == '"')
            notif = -notif;
        else if ((input[start] == ' ' || input[start] == '\t') && notif > 0)
        {
            end = start;
            return (end);
        }
        start++;
    }
    end = start;
    return (end);
}

char *cat_token(char *input, int start, int end)
{
    char *token;
    int i = 0;
    int len = end - start + 1;
    token = c_malloc ((sizeof(char) * len), 1);
    while (start < end)
    {
        token[i] = input[start];
        start++;
        i++;
    }
    token[i] = '\0';
    return (token);
}

t_token **into_tokens(char *input)
{
    int i;
    t_token **tokens;
    int count;
    int start;
    int last_start;

    i = 0;
    start = 0;
    count = tokens_number(input);
    tokens = c_malloc((sizeof(t_token *) * (count + 1)), 1);
    while (i < count)
    {
        tokens[i] = c_malloc(sizeof(t_token), 1);
        if (start == 0)
            last_start = 0;
        else
            last_start = start + 1;
        while (input[last_start] == ' ' || input[last_start] == '\t')
            last_start++;
        start = divide(input, last_start);
        tokens[i]->content = cat_token(input, last_start, start);
        i++;
    }
    tokens[i] = NULL;
    return (tokens);
}
