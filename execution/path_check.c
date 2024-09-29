/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:45:46 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/29 18:35:08 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

char *find_executable(t_line	*final,env_vars *list,char **av)
{
	int i;
	char *command_path;
	char *path;
	char **paths;
	char *to_execute;

	(void)final;
	i = 0;
	path = get_path_from_list(list,"PATH");
	paths = split(path, ':');
	if (!paths || !path)
		return(NULL);
	command_path = malloc(ft_strlenn(av[0]));
	if (!command_path)
		return (NULL);
	command_path = str_joiner("/",av[0]);
	while(paths[i])
	{
		to_execute = malloc(ft_strlenn(command_path) + ft_strlen(paths[i]));
		to_execute = str_joiner(paths[i],command_path);
		if (access(to_execute,F_OK | X_OK) == 0)
			return(free(path),free(command_path),to_execute);
		free(to_execute);
		to_execute = NULL;
		i++;
	}
		free(path);
		free(command_path);
		return(NULL);
}
	
int help_execute_files(t_line *final,char **env,char **av)
{
	int ret;
	int fd_in;
	
	fd_in = dup(0);
	ret = execve(av[0], av, env);
	if(ret == -1)
	{
		if (access(av[0], W_OK) != 0)
		{
			exit_status(1,127);
			perror(final->tokens->content);
			dup2(fd_in,0);
			close(fd_in);
			free_double(av);
			c_malloc(0, 0);
			exit(127);
		}
		exit_status(1,127);
		perror(final->tokens->content);
		dup2(fd_in,0);
		free_double(av);
		close(fd_in);
		free_double(av);
		c_malloc(0, 0);
		exit(127);
	}
	return (ret);
}

char **fake_env(void)
{
	char **env;
	char *pwd;
	
	pwd = getcwd(NULL,0);
	env = malloc(sizeof(char *) *5);
	env[0] = str_joiner("PWD=",pwd);
	env[1] = strdup("SHLVL=1");
	env[2] = strdup("_=/usr/bin/env");
	env[3] = strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	env[4]= NULL; 
	return(env);
}

char *get_path_from_list(env_vars *list,char *str)
{
	char *path;
	env_vars	*temp;

	temp = list;
	if (!temp || temp == NULL)
		return(NULL);
	while (temp)
	{
		if(ft_strcmp(temp->vars,str) == 0)
		{
			path = strdup(temp->var_value);
			return(path);
		}
		temp = temp-> next;
	}
	return(NULL);
}