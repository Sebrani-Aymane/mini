/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:22:49 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/07 02:53:02 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calculate_new_token_len(char *token, char *value, char *name, int *ig_d)
{
	char	*pos;
	int		name_len;
	int		token_len;
	int		value_len;

	pos = ft_strstr(token, name);
	if (*(pos - 1) != '$')
	{
		pos = ft_strstr(pos + ft_strlenn(name), name);
	}
	name_len = ft_strlen(name);
	token_len = ft_strlen(token);
	value_len = ft_strlen(value);
	if (!ft_strcmp(name, "~"))
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
	pos = ft_strstr(token, name);
	if (*(pos - 1) != '$')
	{
		pos = ft_strstr(pos + ft_strlenn(name), name);
	}
	new_token = c_malloc(sizeof(char) * (new_token_len + 1), 1);
	ft_strncpy(new_token, token, ignore_dollar);
	new_token[ignore_dollar] = '\0';
	ft_strcat(new_token, value);
	ft_strcat(new_token, pos + ft_strlen(name));
	return (new_token);
}

char	*check_value(char *value, char *name, t_token *temp)
{
	if (value && ft_strchr(value, ' '))
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

char	*counter_loop(int counter, t_token *temp, t_env_vars *l_env, int *notif)
{
	char			*name;
	char			*value;
	char			*new_token;
	static int		start;

	while (counter)
	{
		name = variable_name(temp->content, &start);
		if (!ft_strcmp(name, "\0"))
		{
			*notif = 1;
			counter--;
			continue ;
		}
		value = get_value(l_env, name, NULL, 0);
		value = check_value(value, name, temp);
		if (!ft_strcmp(name, "_") && !ft_strcmp(value, "/usr/bin/env"))
			value = ft_strdup("env");
		new_token = replace_value(temp->content, value, name);
		temp->content = new_token;
		counter--;
	}
	start = 0;
	return (new_token);
}

void	expand(t_token **tokens, t_env_vars *list_env)
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
			if (check_edge_case(new_token))
				tokens[i]->content = pass_dollar(new_token);
		i++;
	}
}
