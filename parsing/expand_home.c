/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:40:58 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/01 21:44:07 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	can_expand_home(char *input)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (input && input[i])
	{
		if (input[i] == '"')
			d_quote = !d_quote;
		else if (input[i] == '\'')
			s_quote = !s_quote;
		if (input[i] == '~' && (s_quote || d_quote))
			return (0);
		i++;
	}
	return (1);
}

void	expand_home(t_token **tokens, env_vars *list_env)
{
	int		i;
	char	*value;
	char	*new_token;

	i = 0;
	while (tokens && tokens[i])
	{
		if (ft_strchr(tokens[i]->content, '~'))
		{
			if (can_expand_home(tokens[i]->content))
			{
				value = get_value(list_env, "HOME", NULL, 0);
				new_token = replace_value(tokens[i]->content, value, "~");
				tokens[i]->content = new_token;
			}
		}
		i++;
	}
}
