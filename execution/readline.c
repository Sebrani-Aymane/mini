/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:21:00 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/08 18:46:29 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

void execute_builtins(char* builtin, t_line *final, env_vars **list,char **env)
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
			envpp(*list);
		else
			export_all(*list,final);
	}
	
	else if (strcmp(builtin, "env") == 0)
    	envpp(*list);
	else if (strcmp(builtin, "cd") == 0)
	{
		l = chdirr(env,final);
		if (l == -1)
			printf("%s: No such file or directory\n",final->tokens->next->content);
	}
	else if (strcmp(builtin, "unset") == 0)
	{
		unset(*list, final);
	}
	else if (strcmp(builtin, "exit") == 0)
		exit(0);
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
		return -1;
	paths = split(path, ':');
	if (final->tokens->content[i] != '/')
	{
		command_path  = str_joiner("/",final->tokens->content);
		int lenght1= ft_strlen(command_path);
		if (!paths)
			return -1;
		while(paths[i])
		{
			lenght = ft_strlen(paths[i]);
			to_excute = malloc(lenght + lenght1);
			if (!to_excute)
				return -1;
			to_excute = str_joiner(paths[i],command_path);
			if (access(to_excute, X_OK) == 0)
				execve(to_excute, av, env); 
			else
				free(to_excute);
			i++;
		}
	}
	else
	{
		ret = execve(final->tokens->content, av, env);
		if(ret == -1)
			printf("minishell: %s: No such file or directory\n",final->tokens->content);
	}
	free_double(paths);
	free(command_path);
	return 2;
}

void free_double(char **str)
{
	int j;

	j = 0;
	while (str[j])
		free(str[j++]);
	free(str);
}