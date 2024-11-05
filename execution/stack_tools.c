/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:21:34 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/05 16:13:05 by asebrani         ###   ########.fr       */
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
		write(2, "minishell: export: ", 19);
		write(2, str, ft_strlenn(str));
		write(2, " not a valid identifier\n", 24);
		return (0);
	}
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
		{
			write(2, "minishell: export: ", 19);
			write(2, str, ft_strlenn(str));
			write(2, " not a valid identifier\n", 24);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_builtin(t_line *final, t_env_vars *list, char **env)
{
	char	**builtins;
	int		j;

	(void)env;
	(void) list;
	builtins = split("cd echo pwd export unset env exit", ' ');
	j = -1;
	while (builtins[++j])
		if (final -> tokens && ft_strcmp(final->tokens->content,
				builtins[j]) == 0)
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

int	handle_cd_home(char **env)
{
	char	*home;
	int		res;

	home = get_path(env, "HOME=");
	if (!home)
		return (write(2, "minishell: cd: HOME not set\n", 28), 0);
	res = chdir(home);
	return (res);
}

int	cd_helper(t_line *final, t_env_vars *list, char **env)
{
	int		res;
	char	*pwd_bfr_cd;
	char	*tmp;

	res = 0;
	pwd_bfr_cd = get_path_from_list(list, "PWD");
	if (!final->tokens->next)
	{
		res = handle_cd_home(env);
		return (res);
	}
	res = chdir(final->tokens->next->content);
	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		if (!ft_strncmp(final->tokens->next->content, "..", 2))
			chdiir_help(final, list, pwd_bfr_cd);
		else if (!ft_strcmp(final->tokens->next->content, "."))
			chdiir_help2(final, list, pwd_bfr_cd);
		res = 0;
	}
	return (free(tmp), res);
}
