/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:45:46 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/25 00:56:49 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

char	*find_executable(t_line	*final, env_vars *list, char **av)
{
	int		i;
	char	*command_path;
	char	*path;
	char	**paths;
	char	*to_execute;

	(void)final;
	i = 0;
	path = get_path_from_list(list, "PATH");
	paths = split(path, ':');
	if (!paths || !path)
		return (NULL);
	command_path = c_malloc(ft_strlenn(av[0]), 1);
	if (!command_path)
		return (NULL);
	command_path = str_joiner("/", av[0]);
	while (paths[i])
	{
		to_execute = c_malloc(ft_strlenn(command_path)
		+ ft_strlen(paths[i]), 1);
		to_execute = str_joiner(paths[i],command_path);
		if (access(to_execute,F_OK | X_OK) == 0)
			return(to_execute);
		to_execute = NULL;
		i++;
	}
	return (NULL);
}
	
int help_execute_files(t_line *final,char **env,char **av)
{
	int ret;

	ret = execve(av[0], av, env);
	if(ret == -1)
	{
		if (is_dir(av[0]) != 0)
		{
			write(2, "minishell: ", 11);
            write(2, av[0], ft_strlenn(av[0]));
            write(2, ": is a directory\n", 17);
			c_malloc(0, 0);
			exit(126);
		}
		perror(final->tokens->content);
		c_malloc(0, 0);
		exit(128);
	}
	return (ret);
}

char **fake_env(void)
{
	char **env;
	char *pwd;

	pwd = getcwd(NULL,0);
	env = c_malloc(sizeof(char *) *5, 1);
	env[0] = str_joiner("PWD=", pwd);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	env[4]= NULL; 
	return (env);
}

char *get_path_from_list(env_vars *list,char *str)
{
	char 		*path;
	env_vars	*temp;

	temp = list;
	if (!temp || temp == NULL)
		return(NULL);
	while (temp)
	{
		if(ft_strcmp(temp->vars,str) == 0)
		{
			path = ft_strdup(temp->var_value);
			return(path);
		}
		temp = temp-> next;
	}
	return(NULL);
}


char	*ft_strdup(char *s1)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(s1);
	str = c_malloc(j + 1, 1);
	if (str == 0)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}