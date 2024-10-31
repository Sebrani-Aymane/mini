/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:24:23 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/31 21:26:45 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_space(char *input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		while ((input[i] >= 9 && input[i] <= 13) || input[i] == ' ' )
			i++;
		if (input[i])
			return (0);
	}
	return (1);
}

void	check_token_dollar(t_token **token)
{
	int	i;

	i = 0;
	while (token && token[i])
	{
		if (i != 0 && !strcmp(token[i - 1]->content, "<<"))
			token[i]->need_expand = 0;
		else if (token[i]->content && ft_strchr(token[i]->content, '$'))
			token[i]->need_expand = 1;
		else
			token[i]->need_expand = 0;
		i++;
	}
}

int	more_than_op(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (input && input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			while (input[i] == '<' || input[i] == '>')
			{
				count++;
				i++;
				if (count > 2)
					return (i);
			}
		}
		count = 0;
		i++;
	}
	return (0);
}

int	is_redirection_op(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	dollar_inside_quotes_alone(char *content)
{
	int	i;

	i = 1;
	while (content && content[i] && content[i + 1])
	{
		if (content[i] == '$' && content[i - 1] == '"' && content[i + 1] == '"')
			return (1);
		i++;
	}
	return (0);
}
