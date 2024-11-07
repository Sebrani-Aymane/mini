/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:21:00 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/07 02:58:38 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_pwd_command(t_env_vars *list)
{
	char	*pwd;
	int		flag;	

	flag = 0;
	pwd = pwdd(list);
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		flag = 1;
	}
	if (!pwd)
		pwd = list->pwd;
	ft_putstr(pwd, 1);
	ft_putstr("\n", 1);
	if (flag)
		free(pwd);
	return (0);
}

int	handle_cd_command(char **env, t_line *final, t_env_vars *list)
{
	int	ret;

	exit_status(1, -1);
	ret = chdirr(env, final, list);
	if (ret == -1)
	{
		ret = 1;
		printf("minishell: cd: %s ", final->tokens->next->content);
		printf("no such file or directory\n");
	}
	return (ret);
}

int	execute_blts(char *blt, t_line *final, t_env_vars *list, char **env)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(blt, "echo", 4) == 0)
		echoo(final->tokens);
	else if (ft_strncmp(blt, "pwd", 3) == 0)
		ret = handle_pwd_command(list);
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
		ret = handle_cd_command(env, final, list);
	else if (ft_strncmp(blt, "unset", 5) == 0)
		ret = unset(list, final);
	else if (ft_strncmp(blt, "exit", 4) == 0)
		exitt(final);
	return (ret);
}

int	count_valid_tokens(t_node *tokens)
{
	t_node	*current;
	int		count;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == 1 || current->type == 2)
			count++;
		current = current->next;
	}
	return (count);
}

char	**create_av(t_node *tokens)
{
	t_node	*current;
	char	**av;
	int		i;
	int		count;

	i = 0;
	count = count_valid_tokens(tokens);
	av = c_malloc(sizeof(char *) * (count + 1), 1);
	if (!av)
		return (NULL);
	current = tokens;
	while (current)
	{
		if (current->type == 1 || current->type == 2)
		{
			if (!ft_strcmp(current->content, ""))
				av[i] = NULL;
			else
				av[i] = ft_strdup(current->content);
			i++;
		}
		current = current->next;
	}
	av[i] = NULL;
	return (av);
}
