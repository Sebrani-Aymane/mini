/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 06:25:11 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/01 17:31:53 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_the_thing(char **av,char **env,env_vars *list)
{
	char **builtins;
	int j=0;
	char *str;
	int i;
	i = 1;

	str = get_path(env,"PATH=");
	builtins = split("cd echo pwd export unset env exit", ' ');

	while (builtins[++j])
	{
		if (strcmp(av[0],builtins[j]) == 0)
		{
			list = execute_builtins(builtins[j],av,list,env);
			i = 0;
		}
	}
	if (i)
		excutefilepath(av,str,env);
	free_double(builtins);
}
