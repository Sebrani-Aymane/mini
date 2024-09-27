/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:40:41 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/27 14:19:43 by asebrani         ###   ########.fr       */
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
		i ++;
		while (node->content[i] == 'n')
			i++;
		if (!(node->content[i]))
			return (1);
	}
	return (0);
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
env_vars	*envpp_export(env_vars *list)
{
	env_vars	*tmp;

	tmp = list;
	if (!list)
		return (NULL);
	while (list)
	{
		printf("declare -x %s", list->vars);
		if(list->var_value && *(list->var_value) != '\0')
			printf("=\"%s\"\n", list->var_value);
		else
			printf("\n");
		list = list->next;
	}
	return (tmp);
}
