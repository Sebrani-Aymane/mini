/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:22:49 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/30 21:33:34 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*check_value(char *value, char *name, t_token *temp)
{
	if (value && strchr(value, ' '))
		temp->divide_space = 1;
	else
		temp->divide_space = 0;
	if (value == NULL)
	{
		if (name[0] >= '0' && name[0] <= '9')
			value = copy_str(value, name + 1);
		else
			value = "";
	}
	return (value);
}

char	*counter_loop(int counter, t_token *temp, env_vars *l_env, int *notif)
{
	char	*name;
	char	*value;
	char	*new_token;

	while (counter)
	{
		name = variable_name(temp->content);
		if (!strcmp(name, "\0"))
		{
			*notif = 1;
			counter--;
			continue ;
		}
		value = get_value(l_env, name, NULL, 0);
		value = check_value(value, name, temp);
		if (!strcmp(name, "_") && !strcmp(value, "/usr/bin/env"))
			value = ft_strdup("env");
		new_token = replace_value(temp->content, value, name);
		temp->content = new_token;
		counter--;
	}
	return (new_token);
}

void	expand(t_token **tokens, env_vars *list_env)
{
	int		i;
	char	*new_token;
	int		notif;
	int		counter;

	i = 0;
	while (tokens[i])
	{
		notif = 0;
		counter = dollars_number(tokens[i]->content, tokens[i]->need_expand);
		if (counter == 0)
		{
			i++;
			continue ;
		}
		new_token = counter_loop(counter, tokens[i], list_env, &notif);
		if (!notif)
			tokens[i]->content = new_token;
		else
		{
			if (check_edge_case(new_token))
				tokens[i]->content = pass_dollar(new_token);
		}
		i++;
	}
}