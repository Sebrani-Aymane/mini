/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:32:50 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/25 20:20:59 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	chdiir_help(t_line *final, env_vars *list, char *pwd)
{
	t_node		*token;
	env_vars	*temp;

	token = final->tokens->next;
	temp = list;
	while (temp)
	{
		if (!ft_strncmp(temp->vars, "OLDPWD", 6)
			|| !ft_strncmp(temp->vars, "PWD", 3))
		{
			if (!ft_strncmp(temp->vars, "OLDPWD", 6))
				temp ->var_value = strdup(pwd);
			else if (!strcmp(temp->vars, "PWD"))
				temp->var_value = str_joiner(get_path_from_list(list,
							"PWD"), "/..");
		}
		temp = temp ->next;
	}
}

void	chdiir_help2(t_line *final, env_vars *list, char *pwd)
{
	t_node		*token;
	env_vars	*temp;

	token = final->tokens->next;
	temp = list;
	while (temp)
	{
		if (!ft_strncmp(temp->vars, "OLDPWD", 6)
			|| !ft_strncmp(temp->vars, "PWD", 3))
		{
			if (!ft_strncmp(temp->vars, "OLDPWD", 6))
				temp->var_value = strdup(pwd);
			else if (!ft_strncmp(temp->vars, "PWD", 3))
				temp->var_value = str_joiner(get_path_from_list(list,
							"PWD"), "/.");
		}
		temp = temp ->next;
	}
}

int	handle_one_blt(t_line *final, char **env, env_vars *list)
{
	int	ret;

	ret = 0;
	handle_redirections(final);
	ret = execute_blts(final->tokens->content, final, list, env);
	if (final->fd_in != 0)
	{
		dup2(final->fd_in, 0);
		close(final->fd_in);
	}
	if (final ->fd_out != 1)
	{
		dup2(final->fd_in, 1);
		close(final->fd_out);
	}
	return (ret);
}

int	exit_status(int type, int value)
{
	static int	var;

	if (type == GET)
		return (var);
	if (type == SET)
		var = value;
	return (var);
}
