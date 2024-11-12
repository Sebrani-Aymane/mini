/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:18:51 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/12 18:41:30 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_variable(t_env_vars **env, t_env_vars *curr, t_env_vars *prev)
{
	if (!prev)
		*env = curr->next;
	else
		prev->next = curr->next;
	curr->vars = NULL;
	curr->var_value = NULL;
	curr = NULL;
	return (0);
}

void	find_and_unset_variable(t_env_vars **env_bkp, char *content)
{
	t_env_vars	*curr;
	t_env_vars	*prev;
	int			len;

	prev = NULL;
	curr = *env_bkp;
	len = ft_strlenn(content);
	while (curr)
	{
		if (ft_strncmp(curr->vars, content, len) == 0)
			unset_variable(env_bkp, curr, prev);
		prev = curr;
		curr = curr->next;
	}
}

int	process_unset(t_env_vars *env_bkp, t_node *current)
{
	t_env_vars	*curr;
	t_env_vars	*prev;
	int			ret;
	int			len;

	prev = NULL;
	while (current)
	{
		if (check_key_un(current->content) == 1
			&& ft_strncmp("_", current->content, len))
		{
			ret = 0;
			curr = env_bkp;
			len = ft_strlenn(current->content);
			find_and_unset_variable(&env_bkp, current->content);
		}
		else
			ret = 1;
		current = current->next;
	}
	return (ret);
}

int	unset(t_env_vars *env, t_line *final)
{
	t_node	*current;
	int		res;

	if (!env || !final->tokens->next)
		return (1);
	current = final->tokens->next;
	res = process_unset(env, current);
	return (res);
}

int	check_exit_stat(t_line *final)
{
	t_node	*curr;
	int		i;

	i = 0;
	curr = final->tokens->next;
	if (!curr)
		return (0);
	while (curr->content[i])
	{
		if (curr->content[i] == '+' || curr->content[i] == '-')
			i++;
		if (ft_isalpha(curr->content[i]))
			return (0);
		i++;
	}
	return (1);
}
