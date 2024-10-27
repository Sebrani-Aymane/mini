/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:18:51 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/27 00:30:59 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_variable(env_vars **env, env_vars *curr, env_vars *prev)
{
	if (!prev)
		*env = curr->next;
	else
		prev->next = curr->next;
	curr->vars = NULL;
	curr->var_value = NULL;
	return (0);
}

int	process_unset(env_vars *env_bkp, t_node *current)
{
	env_vars	*curr;
	env_vars	*prev;
	int			ret;

	prev = NULL;
	while (current)
	{
		if (check_key(current->content) == 1)
		{
			ret = 0;
			curr = env_bkp;
			while (curr)
			{
				if (ft_strcmp(curr->vars, current->content) == 0)
					unset_variable(&env_bkp, curr, prev);
				prev = curr;
				curr = curr->next;
			}
		}
		else
			ret = 1;
		current = current->next;
	}
	return (ret);
}

int	unset(env_vars *env, t_line *final)
{
	t_node	*current;

	if (!env || !final->tokens->next)
		return (1);
	current = final->tokens->next;
	return (process_unset(env, current));
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
