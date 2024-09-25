/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:45:46 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/25 18:41:56 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_executable(t_line	*final,char **env,char **av)
{
	int i;
	char *command_path;
	char *path;
	char **paths;
	char *to_execute;

	(void)final;
	i = 0;
	path = get_path(env,"PATH=");
	paths = split(path, ':');
	if (!paths)
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
			return(to_execute);
		free(to_execute);
		to_execute = NULL;
		i++;
	}
		free (path);
		free(command_path);
		return(NULL);
}
	
int help_execute_files(t_line *final,char **env,char **av)
{
	int ret;
	int fd_in;
	
	fd_in = dup(0);
	ret = execve(final->tokens->content, av, env);
	if(ret == -1)
	{
		free_double(av);
		if (access(av[0], W_OK) != 0)
		{
			perror(final->tokens->content);
			dup2(fd_in,0);
			close(fd_in);
			exit_status(1,0);
			exit(0);
		}
		perror(final->tokens->content);
		dup2(fd_in,0);
		close(fd_in);
		exit_status(1,0);
		exit(0);
	}
	return (ret);
}