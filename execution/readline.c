/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:21:00 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/25 18:43:40 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

env_vars *execute_builtins(char* builtin, t_line *final, env_vars *list,char **env)
{
	(void)env;
	int l = 0;

	handle_redirections(final);
    if (strcmp(builtin, "echo") == 0)
        echoo(final);
    else if (strcmp(builtin, "pwd") == 0) 
        pwdd(0);
    else if (strcmp(builtin, "export") == 0)
	{
		if (!(final->tokens->next))
			envpp_export(list);
		else
			export_all(list,final);
	}
	else if (strcmp(builtin, "env") == 0)
    	envpp(list);
	else if (strcmp(builtin, "cd") == 0)
	{
		l = chdirr(env,final,list);
		if (l == -1)
		{
			exit_status(1,1);
			perror(final->tokens->content);
		}
	}
	else if (strcmp(builtin, "unset") == 0)
	{
		unset(list, final);
	}
	else if (strcmp(builtin, "exit") == 0)
		exitt(list, final);
	return(list);
}

char **create_av(t_node *tokens)
{
	t_node *current = tokens;
	int count = 0;
	char **av;
	int i = 0;

	while (current)
	{
		if ((current->type == 1 || current->type == 2))
			count++;
		current = current->next;
	}
	av = malloc (sizeof(char *) * (count+1));
	current = tokens;
	while (current)
	{
		if ((current->type == 1 || current->type == 2))
		{
			av[i] = strdup(current->content);
			i++;
		}
		current = current->next;
	}
	av[i] = NULL;
	return av;
}

int excutefilepath(t_line *final,env_vars *list,char **env)
{
	char *to_do;
	int ret = 2;
	(void)list;
	
	char **av = create_av(final->tokens);
	if (!check_file_path(final))
	{
		to_do = find_executable(final,env,av);
		if (to_do)
		{
			exit_status(1, 0);
			ret = execve(to_do, av, env);
		}
		else
		{
			exit_status(1,127);
			write(2,av[0],ft_strlen(av[0]));
			write(2,": command not found\n",20);
		}
	}
	else
		help_execute_files(final,env,av);
	return ret;
}

void free_double(char **str)
{
	int j;

	j = 0;
	while (str[j])
		free(str[j++]);
	free(str);
}