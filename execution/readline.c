/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:21:00 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/02 23:23:29 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

env_vars *execute_builtins(char* builtin, t_line *final, env_vars *list,char **env)
{
	(void)env;
	
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
	// else if (strcmp(builtin, "cd") == 0)
	// {
	// 	//l = chdirr(env,f);
	// 	if (l == -1)
	// 		printf("%s: No such file or directory\n",final->tokens->next->content);

	else if (strcmp(builtin, "unset") == 0)
	{
		unset(list, final);
	}
	else if (strcmp(builtin, "exit") == 0)
		exitt (list, final);	
	return(list);
}
char **create_av(t_node *tokens)
{
	t_node *current = tokens;
	char **av = malloc (sizeof(char *) * (ft_lstsize(tokens) + 1));
	int i = 0;
	while (current)
	{
		av[i] = strdup(current->content);
		current = current->next;
		i++;
	}
	av[i] = NULL;
	return av;
}

void excutefilepath(t_line *final,char *path,char **env)
{
	char *to_excute;
	int i=0;
	char **paths;
	char *command_path;
	int pid;
	char **av = create_av(final->tokens);
	pid = fork();
	if (pid == 0)
	{
	int lenght = ft_strlen(final->tokens->content);
	command_path = malloc(lenght);
	if (!command_path)
		return;
	command_path  = str_joiner("/",final->tokens->content);
	int lenght1= ft_strlen(command_path);
	paths = split(path, ':');
	if (!paths)
		return;
	while(paths[i])
	{
		lenght = ft_strlen(paths[i]);
		to_excute = malloc(lenght + lenght1);
		if (!to_excute)
			return;
		to_excute = str_joiner(paths[i],command_path);
		if (access(to_excute, X_OK) == 0)
			execve(to_excute, av, env); 
		else
			free(to_excute);
		i++;
	}
	free_double(paths);
	free(command_path);
	exit(1);
	}
	else
		wait(NULL);
	return;
}

void free_double(char **str)
{
	int j;

	j = 0;
	while (str[j])
		free(str[j++]);
	free(str);
}