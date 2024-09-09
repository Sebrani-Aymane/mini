/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:21:00 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/09 16:36:07 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

env_vars *execute_builtins(char* builtin, t_line *final, env_vars *list,char **env)
{
	(void)env;
	int l = 0;
	
    if (strcmp(builtin, "echo") == 0)
        echoo(final);
    else if (strcmp(builtin, "pwd") == 0) 
        pwdd(1);
    else if (strcmp(builtin, "export") == 0)
	{
		if (!(final->tokens->next))
			envpp(list);
		else
			export_all(list,final);
	}
	
	else if (strcmp(builtin, "env") == 0)
    	envpp(list);
	else if (strcmp(builtin, "cd") == 0)
	{
		l = chdirr(env,final);
		if (l == -1)
			printf("%s: No such file or directory\n",final->tokens->next->content);
	}
	else if (strcmp(builtin, "unset") == 0)
	{
		unset(list, final);
	}
	else if (strcmp(builtin, "exit") == 0)
	{
		c_malloc(0, 0);
		exit(0);
	}
	return(list);
}
char **create_av(t_node *tokens)
{
	t_node *current = tokens;
	int count = 0;
	while (current && strlen(current->content) != 0)
	{
		count ++;
		current = current->next;
	}
	char **av = malloc (sizeof(char *) * (count + 1));
	int i = 0;
	current = tokens;
	while (current)
	{
		if (strlen(current->content) != 0)
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
	char *to_excute;
	int i=0;
	char **paths;
	char *command_path;
	char *path;
	int ret =0;


	char **av = create_av(final->tokens);
	int lenght = ft_strlen(final->tokens->content);
	
	path = get_path_from_list(list);
	command_path = malloc(lenght);
	if (!command_path)
		return 0;
	paths = split(path, ':');
	
	if (final->tokens->content[i] != '/')
	{
		command_path  = str_joiner("/",final->tokens->content);
		int lenght1= ft_strlen(command_path);
		if (!paths)
			return 0 ;
		while(paths[i])
		{
			lenght = ft_strlen(paths[i]);
			to_excute = malloc(lenght + lenght1);
			if (!to_excute)
				return 0;
			to_excute = str_joiner(paths[i],command_path);
			if (access(to_excute, X_OK) == 0)
				execve(to_excute, av, env); 
			else
				free(to_excute);
			i++;
		}
		free (to_excute);
	}
	else
	{
		ret = execve(final->tokens->content, av, env);
		if(ret == -1)
			printf("minishell: %s: No such file or directory\n",final->tokens->content);
	}
	
	free_double(paths);
	free(command_path);
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