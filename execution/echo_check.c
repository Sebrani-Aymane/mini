/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:40:41 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/09 23:00:17 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_eccho(t_node *node)
{
	int i = 0;
	if (!node) 
		return(0);
	if (node->content[i] == '-' && node->content[i + 1] == 'n')
	{
		i++;
		while (node->content[i] == 'n')
			i++;
		if (!(node->content[i]))
			return (1);
	}
	return(0);
}