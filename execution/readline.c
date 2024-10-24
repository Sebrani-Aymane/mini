/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:21:00 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/23 06:01:07 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_blts(char *blt, t_line *final,
						env_vars *list, char **env)
{
	int		ret;
	char	*pwd;

	ret = 0;
	if (strcmp(blt, "echo") == 0)
		echoo(final);
	else if (strcmp(blt, "pwd") == 0)
	{
		pwd = pwdd(list);
		ft_putstr(pwd,1 );
		ft_putstr("\n", 1);
	}
	else if (strcmp(blt, "export") == 0)
	{
		if (!(final->tokens->next))
			envpp_export(list);
		else
			ret = export_all(list, final);
	}
	else if (strcmp(blt, "env") == 0)
		envpp(list);
	else if (strcmp(blt, "cd") == 0)
	{
		ret = chdirr(env, final, list);
		if (ret == -1)
		{
			ret = 1;
			exit_status(1, -1);
			printf("minishell: cd: %s", final->tokens->next->content);
			printf("no such file or directory\n");
		}
	}
	else if (strcmp(blt, "unset") == 0)
		ret = unset(list, final);
	else if (strcmp(blt, "exit") == 0)
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
			ret = execve(to_do, av, env);
		}
		else if (!to_do && get_path_from_list(list, "PATH"))
		{
			str = str_joiner(av[0], " :command not found\n");
			exit_status(1, 127);
			write(2, "minishell: ", 11);
			write(2, str, ft_strlenn(av[0]) + 20);
			c_malloc(0, 0);
			exit(127);
		}
		if (!to_do && !get_path_from_list(list, "PATH"))
		{
			exit_status(1, 127);
			c_malloc(0, 0);
			exit(127);
		}
	}
	else
		help_execute_files(final, env, av);
	return (ret);
}

void	free_double(char **str)
{
	int	j;

	j = 0;
	while (str[j])
		free (str[j++]);
	free (str);
}
