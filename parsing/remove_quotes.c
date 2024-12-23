/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:38:59 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/07 03:00:44 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rem_quotes_while(char *content, int *i, char *final, int *j)
{
	char	c;

	c = content[(*i)++];
	while (content[*i])
	{
		if (content[*i] != c)
			final[(*j)++] = content[*i];
		else if (content[*i] == c)
			break ;
		(*i)++;
	}
}

char	*remove_quotes(char *content, int i, int j)
{
	char	*final;

	final = c_malloc(sizeof(char) * ft_strlen(content) + 1, 1);
	if (!final)
		return (NULL);
	while (content && content[i])
	{
		if (content[i] == '\'' || content[i] == '\"')
		{
			rem_quotes_while(content, &i, final, &j);
		}
		else
			final[j++] = content[i];
		if (content[i])
			i++;
	}
	final[j] = '\0';
	return (final);
}

void	final_tokens(t_node *token)
{
	t_node	*current;
	char	*final;

	current = token;
	while (current)
	{
		final = remove_quotes(current->content, 0, 0);
		if (final)
		{
			current->content = final;
		}
		current = current->next;
	}
}
