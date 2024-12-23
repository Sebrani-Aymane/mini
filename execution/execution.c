/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:25:24 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/12 20:13:15 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	when_not_blt(t_line *final, char **env, t_env_vars *list)
{
	if (executefilepath(final, env, list) == 2)
	{
		if (final->tokens->type == 1 || final->tokens->type == 2)
		{
			exit_status(1, 127);
			write(2, final->tokens->content,
				ft_strlenn(final->tokens->content));
			write(2, ": No such file or directory\n", 28);
			c_malloc(0, 0);
			exit(127);
		}
	}
}

void	errorrr(char *av)
{
	char	*str;

	str = str_joiner(av, " :command not found\n");
	exit_status(1, 127);
	write(2, "minishell: ", 11);
	write(2, str, ft_strlenn(av) + 20);
	exit(127);
}

int	handle_command_execution(char **av, char **env, t_env_vars *list)
{
	char	*to_do;

	to_do = find_executable(NULL, list, av);
	if (to_do)
	{
		exit_status(1, 0);
		execve(to_do, av, env);
	}
	else if (!to_do && get_path_from_list(list, "PATH"))
		errorrr(av[0]);
	if (!to_do && !get_path_from_list(list, "PATH"))
	{
		execve(av[0], av, env);
		errorrr(av[0]);
	}
	return (0);
}

int	executefilepath(t_line *final, char **env, t_env_vars *list)
{
	char	**av;

	av = create_av(final->tokens, 0);
	if (!av || !*av)
		return (0);
	if (!check_file_path(final))
		handle_command_execution(av, env, list);
	else
		help_execute_files(final, env, av);
	return (2);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
