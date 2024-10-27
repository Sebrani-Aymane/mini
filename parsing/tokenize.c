/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:49:18 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/27 17:27:37 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_quotes(char *input, int *inside_d, int *inside_s, int i)
{
	if (input[i] == '"' && (*inside_s) == 0)
		(*inside_d) = !(*inside_d);
	else if (input[i] == '\'' && *inside_d == 0)
		(*inside_s) = !(*inside_s);
}

int	tokens_number(char *input, int i, int count, int i_d)
{
	int	end;
	int	i_s;

	i_s = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	end = ft_strlen(input);
	while (end > 0 && (input[end] == ' ' || input[end] == '\t'))
		end--;
	if (i == end)
		return (0);
	while (i < end)
	{
		if (input[i] == '"' || input[i] == '\'')
			check_quotes(input, &i_d, &i_s, i);
		else if ((input[i] == ' ' || input[i] == '\t') && !i_d && !i_s)
		{
			count++;
			while ((input[i] == ' ' || input[i] == '\t') && !i_d && !i_s)
				i++;
			i--;
		}
		i++;
	}
	return (count + 1);
}


int	divide(char *input, int start, int inside_d, int inside_s)
{
	int	end;
	int	last;

	if (start == 0)
	{
		while (input[start] == ' ' || input[start] == '\t')
			start++;
	}
	last = strlen(input) - 1;
	while (last > 0 && (input[last] == ' ' || input[last] == '\t'))
		last--;
	while (start <= last)
	{
		if (input[start] == '"' || input[start] == '\'')
			check_quotes(input, &inside_d, &inside_s, start);
		else if ((input[start] == ' ' || input[start] == '\t')
			&& !inside_d && !inside_s)
		{
			end = start;
			return (end);
		}
		start++;
	}
	end = start;
	return (end);
}

char	*cat_token(char *input, int start, int end)
{
	char	*token;
	int		i;
	int		len;

	i = 0;
	len = end - start + 1;
	token = c_malloc ((sizeof(char) * len), 1);
	if (!token)
		return (NULL);
	while (start < end)
	{
		token[i] = input[start];
		start++;
		i++;
	}
	token[i] = '\0';
	return (token);
}

t_token	**into_tokens(char *input, int i, int start)
{
	t_token	**tokens;
	int		count;
	int		last_start;

	count = tokens_number(input, 0, 0, 0);
	tokens = c_malloc((sizeof(t_token *) * (count + 1)), 1);
	if (!tokens)
		return (NULL);
	while (i < count)
	{
		tokens[i] = c_malloc(sizeof(t_token), 1);
		if (!tokens[i])
			return (NULL);
		if (start == 0)
			last_start = 0;
		else
			last_start = start + 1;
		while (input[last_start] == ' ' || input[last_start] == '\t')
			last_start++;
		start = divide(input, last_start, 0, 0);
		tokens[i]->content = cat_token(input, last_start, start);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
