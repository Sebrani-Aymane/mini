/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:18:51 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/22 16:01:02 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

int	unset_variable(env_vars **env, env_vars *curr, env_vars *prev)
{
	if (!prev)
		*env = curr->next;
	else
		prev->next = curr->next;
	curr->vars = NULL;
	curr->var_value = NULL;
	return (1);
}

int	process_unset(env_vars *env_bkp, t_node *current)
{
	env_vars	*curr;
	env_vars	*prev;

	prev = NULL;
	while (current)
	{
		if (check_key(current->content) == 1)
		{
			curr = env_bkp;
			while (curr)
			{
				if (ft_strcmp(curr->vars, current->content) == 0)
					return (unset_variable(&env_bkp, curr, prev));
				prev = curr;
				curr = curr->next;
			}
		}
		current = current->next;
	}
	return (0);
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
void	exitt(env_vars *env, t_line *final)
{
	int			num;
	t_node		*current;

	(void)env;
	num = 0;
	current = final->tokens->next;
	if (current)
	{
		if (current->next && (check_exit_stat(final)
			|| (ft_strlenn(current->content) < 19 && num < (int)9223372036854775807)))
		{
			printf("minishell$: exit: too many arguments\n");
			exit_status(1, 1);
			return ;
		}
		num = ft_atoii(current->content);
		if (!check_exit_stat(final)  || num > (int)9223372036854775807 || num < (int)9223372036854775807)
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", current->content);
			exit_status(1, 255);
			c_malloc(0, 0);
			exit(255);
		}
	}
	else
	{
		c_malloc(0, 0);
		exit(0);
	}
	if (num > 255)
		num = num % 255;
	exit_status(1, num);
	c_malloc(0, 0);
	exit(num);
}