/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 06:25:11 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/02 23:12:43 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void handle_pipe(t_line *final)
{
	if (!final->next)
		return;
	else
	
		while (final)
		{
			
		}
}
void execute_the_thing(t_line *final,char **env,env_vars *list)
{
	char **builtins;
	int j=0;
	char *str;
	int i;
	i = 1;
	
	str = get_path(env,"PATH=");
	builtins = split("cd echo pwd export unset env exit", ' ');//echo hello
	
	while (builtins[++j])
	{
		if (strcmp(final->tokens->content,builtins[j]) == 0)
		{
			list = execute_builtins(builtins[j],final ,list,env);
			i = 0;
		}
	}
	if (i)
		excutefilepath(final,str,env);
	free_double(builtins);
}
