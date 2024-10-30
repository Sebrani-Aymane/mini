/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:19:28 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/30 21:23:06 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inside_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	if ((str[0] == '"' || str[0] == '\'') && (str[len - 1] == '"'
			|| str[len - 1] == '\''))
		return (1);
	return (0);
}

int	contains_only_symbol(char *str)
{
	return (!strcmp(str, ">") || !strcmp(str, "<") || !strcmp(str, "<<")
		|| !strcmp(str, ">>") || !strcmp(str, "|"));
}

int	contains_symbol(char *str)
{
	return (ft_strchr(str, '>') || ft_strchr(str, '<') || ft_strchr(str, '|'));
}

int	can_expand(char *input)
{
	int	d_quote;
	int	s_quote;
	int	i;

	d_quote = 0;
	s_quote = 0;
	i = 0;
	while (input && input[i])
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

int	check_edge_case(char *content)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (content && content[i])
	{
		if (content[i] == '"' && s_quote == 0)
			d_quote = !d_quote;
		if (content[i] == '\'' && d_quote == 0)
			s_quote = !s_quote;
		if (content[i] == '$' && !s_quote && !d_quote)
			return (1);
		i++;
	}
	return (0);
}