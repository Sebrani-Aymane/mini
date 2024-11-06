/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:27:48 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/06 19:05:08 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	last_command(t_env_vars *list, t_line *final, int f_s, t_node *curr)
{
	t_env_vars	*curr_list;
	t_node		*last_token;

	curr_list = list;
	if (!list || !final)
		return ;
	while (list)
	{
		if (!ft_strncmp(list->vars, "_", 1))
			break ;
		list = list->next;
	}
	if (f_s > 1 && list)
		list->var_value = ft_strdup("");
	else
	{
		last_token = ft_lstlast(curr);
		if (!ft_strcmp(last_token->content, "env") && list)
			list->var_value = ft_strdup("/usr/bin/env");
		else
			list->var_value = ft_strdup(last_token->content);
	}
	list = curr_list;
}

char	*copy_str(char *dest, char *src)
{
	int	i;

	dest = c_malloc(sizeof(char) * (ft_strlenn(src) + 1), 1);
	i = 0;
	if (!src)
		return (NULL);
	while (*src)
	{
		dest[i] = *src;
		i++;
		src++;
	}
	dest[i] = '\0';
	return (dest);
}

int	pass_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

int	pass_spaces_end(char *input)
{
	int	i;

	i = ft_strlenn(input) - 1;
	while (input[i] == ' ' || input[i] == '\t')
		i--;
	return (i);
}

void	copy_without_spaces(char *dst, char *src)
{
	int	i;
	int	j;
	int	k;

	i = pass_spaces(src);
	j = ft_strlenn(src) - 1;
	k = 0;
	if (!src && !*src)
		return ;
	while (src[j] == ' ' || src[j] == '\t')
		j--;
	while (i <= j)
	{
		dst[k] = src[i];
		i++;
		k++;
	}
	dst[k] = '\0';
}
