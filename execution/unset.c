/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:18:51 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/23 00:11:09 by asebrani         ###   ########.fr       */
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

int is_valid_number(char *str)
{
    int i;
    
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

long long ft_atoll(char *str)
{
    long long result;
    int sign;
    int i;
    
    result = 0;
    sign = 1;
    i = 0;
    
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] && ft_isdigit(str[i]))
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result * sign);
}

void exitt(env_vars *env, t_line *final)
{
    t_node *arg;
    long long num;
    
    (void)env;
    arg = final->tokens->next;
    
    if (!arg)
    {
        printf("exit\n");
        c_malloc(0, 0);
        exit(exit_status(0, 0));
    }
    
    if (!is_valid_number(arg->content))
    {
        printf("exit\n");
        printf("minishell: exit: %s: numeric argument required\n", arg->content);
        exit_status(1, 255);
        c_malloc(0, 0);
        exit(255);
    }
    
    num = ft_atoll(arg->content);
    if (arg->next)
    {
        printf("minishell: exit: too many arguments\n");
        exit_status(1, 1);
        return;
    }
    
    printf("exit\n");
    num = (num % 256 + 256) % 256;
    exit_status(1, num);
    c_malloc(0, 0);
    exit(num);
}