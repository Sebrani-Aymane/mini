/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:40:41 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/05 16:10:30 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_eccho(t_node *node)
{
	int	i;

	i = 0;
	if (!node)
		return (0);
	if (node->content[i] == '-' && node->content[i + 1] == 'n')
	{
		i++;
		while (node->content[i] == 'n')
			i++;
		if (!(node->content[i]))
			return (1);
	}
	return (0);
}

void	check_echo_flags(t_node **current, int *newline)
{
	t_node	*tmp;

	tmp = NULL;
	*newline = 1;
	if ((*current)->next)
		*current = (*current)->next;
	else
		*current = NULL;
	if (check_eccho(*current))
	{
		while (check_eccho(*current))
			*current = (*current)->next;
		tmp = *current;
		*newline = 0;
	}
	if (tmp)
		*current = tmp;
}

int	ft_strlenn(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

t_env_vars	*envpp_export(t_env_vars *list)
{
	t_env_vars	*tmp;

	tmp = list;
	if (!list)
		return (NULL);
	while (list)
	{
		printf("declare -x %s", list->vars);
		if (list->var_value && *(list->var_value) != '\0')
			printf("=\"%s\"\n", list->var_value);
		else
			printf("\n");
		list = list->next;
	}
	return (tmp);
}

int	exit_status(int type, int value)
{
	static int	var;

	if (type == GET)
	{
		return (var);
	}
	if (type == SET)
		var = value;
	return (var);
}
