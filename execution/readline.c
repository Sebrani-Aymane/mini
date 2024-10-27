/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:21:00 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/27 04:36:07 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_blts(char *blt, t_line *final,
						env_vars *list, char **env)
{
	int		ret;
	char	*pwd;

	ret = 0;
	if (ft_strncmp(blt, "echo", 4) == 0)
		echoo(final->tokens);
	else if (ft_strncmp(blt, "pwd", 3) == 0)
	{
		pwd = pwdd(list);
		if (!pwd)
			pwd = getcwd(NULL, 0);
		ft_putstr(pwd, 1);
		ft_putstr("\n", 1);
		free(pwd);
	}
	else if (ft_strncmp(blt, "export", 6) == 0)
	{
		if (!(final->tokens->next))
			envpp_export(list);
		else
			ret = export_all(list, final);
	}
	else if (ft_strncmp(blt, "env", 3) == 0)
		envpp(list);
	else if (ft_strncmp(blt, "cd", 2) == 0)
	{
		ret = chdirr(env, final, list);
		exit_status(1, -1);
		if (ret == -1)
		{
			ret = 1;
			printf("minishell: cd: %s", final->tokens->next->content);
			printf("no such file or directory\n");
		}
	}
	else if (ft_strncmp(blt, "unset", 5) == 0)
		ret = unset(list, final);
	else if (ft_strncmp(blt, "exit", 4) == 0)
		exitt(list, final);
	return (ret);
}

char	**create_av(t_node *tokens)
{
	t_node	*current;
	int		count;
	char	**av;
	int		i;

	i = 0;
	current = tokens;
	count = 0;
	while (current)
	{
		if ((current->type == 1 || current->type == 2))
			count++;
		current = current->next;
	}
	av = c_malloc (sizeof(char *) * (count + 1), 1);
	current = tokens;
	while (current)
	{
		if ((current->type == 1 || current->type == 2))
		{
			av[i] = ft_strdup(current->content);
			i++;
		}
		current = current->next;
	}
	av[i] = NULL;
	return (av);
}

int	excutefilepath(t_line *final, env_vars *list, char **env)
{
	char	*to_do;
	int		ret;
	char	**av;
	char	*str;

	(void)list;
	ret = 2;
	av = create_av(final->tokens);
	if (!av || !*av)
		return (0);
	if (!check_file_path(final))
	{
		to_do = find_executable(final, list, av);
		if (to_do)
		{
			exit_status(1, 0);
			execve(to_do, av, env);
		}
		else if (!to_do && get_path_from_list(list, "PATH"))
		{
			str = str_joiner(av[0], " :command not found\n");
			exit_status(1, 127);
			write(2, "minishell: ", 11);
			write(2, str, ft_strlenn(av[0]) + 20);
			exit(127);
		}
		if (!to_do && !get_path_from_list(list, "PATH"))
		{
			exit_status(1, 127);
			exit(127);
		}
	}
	else
		help_execute_files(final, env, av);
	return (ret);
}
