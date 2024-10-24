/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:21:34 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/23 08:35:45 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_key(char *str)
{
	int	i;

	i = 0;
	if (!str || is_space(str) || ft_isalpha(str[i]
			|| str[0] == '_'))
	{
		write(1, "minishell: export: ", 19);
		write(1, str, ft_strlenn(str));
		write(1, " not a valid identifier\n", 24);
		return (0);
	}
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
		{
			write(1, "minishell: export: ", 19);
			write(1, str, ft_strlenn(str));
			write(1, " not a valid identifier\n", 24);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_builtin(t_line *final, env_vars *list, char **env)
{
	char	**builtins;
	int		j;

	(void)env;
	(void) list;
	builtins = split("cd echo pwd export unset env exit", ' ');
	j = -1;
	while (builtins[++j])
		if (final -> tokens && strcmp(final->tokens->content, builtins[j]) == 0)
			return (1);
	return (0);
}

int	check_file_path(t_line *final)
{
	t_node	*current;
	int		i;

	current = final->tokens;
	i = 0;
	if ((!current->content || !current->content)
		&& (!current->next || !current->next->content))
		return (0);
	while (current ->content[i])
	{
		if (current->content[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	cd_helper(t_line *final, env_vars *list, char **env)
{
	char	*home;
	int		res;
	char	*pwd_bfr_cd;

	res = 0;
	pwd_bfr_cd = get_path_from_list(list, "PWD");
	if (!final->tokens->next)
	{
		home = get_path(env, "HOME=");
		if (!home)
			return (write(2, "minishell: cd: HOME not set\n", 28), 0);
		res = chdir(home);
	}
	else
	{
		res = chdir(final->tokens->next->content);
		if (!getcwd(NULL, 0))
		{
			if (!ft_strcmp(final->tokens->next->content, ".."))
				chdiir_help(final, list, pwd_bfr_cd);
			else if (!ft_strcmp(final->tokens->next->content, ".."))
				chdiir_help2(final, list, pwd_bfr_cd);
		}
	}
	return (res);
}
