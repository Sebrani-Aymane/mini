/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:03:15 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/19 14:34:26 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(env_vars *env, t_line *final)
{
	t_node		*current;
	env_vars	*curr;
	env_vars	*prev;
	env_vars	*env_bkp;
	int			ret;

	prev = NULL;
	ret = 0;
	if (!env)
		return (1);
	if (final->tokens->next)
		current = final->tokens->next;
	else
		return (1);
	env_bkp = env;
	while (current)
	{
		ret = check_key(current->content);
		curr = env_bkp;
		while (curr)
		{
			if (ft_strcmp(curr->vars, current->content) == 0)
			{
				if (prev == NULL)
					env = curr->next;
				else
					prev->next = curr->next;
				curr->vars = NULL;
				curr->var_value = NULL;
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
		current = current->next;
	}
	return (ret);
}

int	check_exit_stat(t_line *final)
{
	t_node	*curr;
	int		i;

	i = 0;
	curr = final->tokens->next;
	if (!curr)
		return (0);
	while (curr ->content[i])
	{
		if (curr ->content[i] == '+' || curr ->content[i] == '-')
			i ++;
		if (ft_isalpha(curr->content[i]))
			return (0);
		i ++;
	}
	return (1);
}

void	exitt(env_vars *env, t_line *final)
{
	int			num;
	env_vars	*temp;
	t_node		*current;

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
		if (!check_exit_stat(final) || (ft_strlenn(current->content) > 19 && num > (int)9223372036854775807))
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
	if (env && env->next)
	{
		while (env && env->next)
		{
			temp = env->next;
			env = temp;
		}
	}
	exit_status(1, num);
	env ->exit = num;
	if (num > 255)
	{
		c_malloc(0, 0);
		exit(num % 255);
	}
	c_malloc(0, 0);
	exit(num);
}

int	exit_status(int type, int value)
{
	static int	var;

	if (type == GET)
		return (var);
	else if (type == SET)
	{
		var = value;
		return (var);
	}
	return (var);
}
