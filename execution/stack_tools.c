/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:21:34 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/19 14:33:02 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	if ((c <= 122 && c >= 97) || (c <= 90 && c >= 65))
		return (1);
	else
		return (0);
}

int	is_space(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		return (1);
	return (0);
}

int	check_key(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (printf("'%s' not a valid identifier1\n", str), 0);
	if (is_space(str))
		return (printf("'%s' not a valid identifier2\n", str), 0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (printf("'%s' not a valid identifier3\n", str), 0);
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (printf("'%s' not a valid identifier4\n", str), 0);
		i++;
	}
	return (1);
}

int	check_builtin(t_line *final, env_vars *list, char **env)
{
	char	**builtins;
	int		j;

	(void)env;
	(void) list;
	builtins = split("cd echo pwd export unset env exit", ' ');
	j = -1;
	while (builtins[++j])
		if (final -> tokens && strcmp(final->tokens->content, builtins[j]) == 0)
			return (1);
	return (0);
}

int	check_file_path(t_line *final)
{
	t_node	*current;
	int		i;

	current = final->tokens;
	i = 0;
	if ((!current->content || !current->content)
		&& (!current->next || !current->next->content))
		return (0);
	while (current ->content[i])
	{
		if (current->content[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
