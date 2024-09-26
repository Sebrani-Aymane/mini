/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:22:49 by cbajji            #+#    #+#             */
/*   Updated: 2024/09/26 18:29:30 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	can_expand(char *input)
{
	int	d_quote;
	int	s_quote;
	int	i;

	d_quote = 0;
	s_quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '"' && s_quote == 0)
			d_quote = !d_quote;
		if (input[i] == '\'' && d_quote == 0)
			s_quote = !s_quote;
		if (input[i] == '$' && (d_quote
				|| (!s_quote && !d_quote)))
			return (1);
		i++;
	}
	return (0);
}

int	dollars_number(char *content, int need_exp)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (can_expand(content) && need_exp
		&& !dollar_inside_quotes_alone(content)
		&& strcmp(content, "$"))
	{
		while (content[i])
		{
			if (content[i] == '$' && content[i + 1] && content[i + 1] != ' ')
				counter++;
			i++;
		}
	}
	return (counter);
}

int	find_var_end(char *input, int *start)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '$')
		i++;
	*start = i + 1;
	i++;
	while (input[i] && ((input[i] >= 'a' && input[i] <= 'z')
			|| (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= '0'
				&& input[i] <= '9') || input[i] == '_' || (input[i] == '?'
				&& input[i - 1] && input[i - 1] == '$')))
		i++;
	return (i - 1);
}

char	*variable_name(char *input)
{
	int		start;
	int		end;
	int		len;
	char	*var_name;

	start = 0;
	end = find_var_end(input, &start);
	if ((input[0] == '"' || input[0] == '\'') && input[end + 1] == '\0')
	{
		while (input[end] == '"' || input[end] == '\'')
			end--;
	}
	len = end - start + 1;
	var_name = c_malloc((sizeof(char) * (len + 1)), 1);
	if (var_name)
	{
		strncpy(var_name, input + start, len);
		var_name[len] = '\0';
	}
	return (var_name);
}

char	*get_value(env_vars *list_env, char *name, char *value, int j)
{
	env_vars	*current;

	current = list_env;
	if (!strcmp(name, "?"))
	{
		value = c_malloc(2, 1);
		copy_it(value, ft_itoa(exit_status(2, 0)));
		return (value);
	}
	while (current)
	{
		if (strcmp(name, current->vars) == 0)
		{
			j = ft_strlen(current->var_value);
			value = c_malloc((sizeof(char) * (j + 1)), 1);
			if (!value)
				return (NULL);
			strcpy(value, current->var_value);
			value[j] = '\0';
			return (value);
		}
		current = current->next;
	}
	return (NULL);
}
//ig_d ---> ignore_dollar
int	calculate_new_token_len(char *token, char *value, char *name, int *ig_d)
{
	char	*pos;
	int		name_len;
	int		token_len;
	int		value_len;

	pos = strstr(token, name);
	name_len = strlen(name);
	token_len = strlen(token);
	value_len = strlen(value);
	if (!strcmp(name, "~"))
	{
		*ig_d = pos - token;
		return ((token_len - name_len) + value_len);
	}
	else
	{
		*ig_d = (pos - token) - 1;
		return ((token_len - name_len - 1) + value_len);
	}
}

char	*replace_value(char *token, char *value, char *name)
{
	int		ignore_dollar;
	int		new_token_len;
	char	*pos;
	char	*new_token;

	new_token_len = calculate_new_token_len(token, value, name, &ignore_dollar);
	pos = strstr(token, name);
	new_token = c_malloc(sizeof(char) * (new_token_len + 1), 1);
	strncpy(new_token, token, ignore_dollar);
	new_token[ignore_dollar] = '\0';
	strcat(new_token, value);
	strcat(new_token, pos + strlen(name));
	return (new_token);
}
void expand(t_token **tokens, env_vars *list_env)
{
    int i = 0;
    char *name;
    char *value;
    char *new_token;
    char *temp_token;
    int notif;
    int counter;

    while (tokens[i])
    {
        notif = 0;
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
            if (!strcmp(name, "\0"))
            {
                notif = 1;
                counter--;
                continue ;
            }
            value = get_value(list_env, name, NULL, 0);
			if (value && strchr(value, ' '))
				tokens[i]->divide_space = 1;
			else 
				tokens[i]->divide_space = 0;
            if (value == NULL)
                value = "";
            new_token = replace_value(temp_token, value, name);
            temp_token = new_token;
            counter--;
        }
        if (!notif)
            tokens[i]->content = new_token;
        else
        {
            if (check_edge_case(temp_token))
                    tokens[i]->content = pass_dollar(temp_token);
        }
        i++;
    }
}
// char	*counter_loop(int counter, char *temp, env_vars *l_env, int *notif)
// {
// 	char	*name;
// 	char	*value;
// 	char	*new_token;

// 	while (counter)
// 	{
// 		name = variable_name(temp);
// 		if (!strcmp(name, "\0"))
// 		{
// 			*notif = 1;
// 			counter--;
// 			continue ;
// 		}
// 		value = get_value(l_env, name, NULL, 0);
// 		if (value == NULL)
// 			value = "";
// 		new_token = replace_value(temp, value, name);
// 		temp = new_token;
// 		counter--;
// 	}
// 	return (new_token);
// }

// void	expand(t_token **tokens, env_vars *list_env)
// {
// 	int		i;
// 	char	*new_token;
// 	int		notif;
// 	int		counter;

// 	i = 0;
// 	while (tokens[i])
// 	{
// 		notif = 0;
// 		counter = dollars_number(tokens[i]->content, tokens[i]->need_expand);
// 		if (counter == 0)
// 		{
// 			i++;
// 			continue ;
// 		}
// 		new_token = counter_loop(counter, tokens[i]->content, list_env, &notif);
// 		if (!notif)
// 			tokens[i]->content = new_token;
// 		else
// 		{
// 			if (check_edge_case(new_token))
// 				tokens[i]->content = pass_dollar(new_token);
// 		}
// 		i++;
// 	}
// }
