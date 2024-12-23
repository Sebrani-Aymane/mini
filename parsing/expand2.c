/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:32:42 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/12 00:14:57 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollars_number(char *content, int need_exp, char where)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (need_exp && !dollar_inside_quotes_alone(content)
		&& ft_strcmp(content, "$")
		&& (where == 'h' || can_expand(content)))
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

	while (input && input[*start] && input[*start] != '$')
		(*start)++;
	(*start)++;
	i = *start;
	while (input[i] && ((input[i] >= 'a' && input[i] <= 'z')
			|| (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= '0'
				&& input[i] <= '9') || input[i] == '_' || (input[i] == '?'
				&& input[i - 1] && input[i - 1] == '$')))
		i++;
	return (i - 1);
}

char	*variable_name(char *input, int *start)
{
	int		end;
	int		len;
	char	*var_name;

	end = find_var_end(input, start);
	if (input && (input[0] == '"' || input[0] == '\'')
		&& input[end + 1] == '\0')
	{
		while (input[end] == '"' || input[end] == '\'')
			end--;
	}
	len = end - (*start) + 1;
	var_name = c_malloc((sizeof(char) * (len + 1)), 1);
	if (var_name)
	{
		ft_strncpy(var_name, input + (*start), len);
		var_name[len] = '\0';
	}
	return (var_name);
}

char	*exp_exit_status(char *num)
{
	char	*value;

	num = ft_itoa(exit_status(2, 0));
	value = c_malloc(ft_strlenn(num) + 1, 1);
	copy_it(value, num);
	return (value);
}

char	*get_value(t_env_vars *list_env, char *name, char *value, int j)
{
	t_env_vars	*current;

	current = list_env;
	if (!ft_strcmp(name, "?"))
		return (exp_exit_status(0));
	if (!current->vars)
		return (NULL);
	while (current)
	{
		if (ft_strcmp(name, current->vars) == 0)
		{
			j = ft_strlen(current->var_value);
			value = c_malloc((sizeof(char) * (j + 1)), 1);
			if (!value)
				return (NULL);
			copy_it(value, current->var_value);
			value[j] = '\0';
			return (value);
		}
		current = current->next;
	}
	return (NULL);
}
