/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:06:10 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/08 11:55:34 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchrr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (0);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (!s1)
		return (-1);
	while (i < n - 1 && s1[i] == s2[i] && s2[i] && s1[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

void	exit_help(t_node *arg)
{
	int	len;

	len = ft_strlen(arg->content);
	write(2, "exit\n", 5);
	write(2, "minishell: exit: ", 17);
	write(2, arg->content, len);
	write(2, " numeric argument required\n", 27);
	exit_status(1, 255);
	c_malloc(0, 0);
	exit (255);
}

void	exit_helper(void)
{
	write(2, "minishell: exit: too many arguments\n", 36);
	exit_status(1, 1);
	return ;
}

void	exitt(t_line *final)
{
	t_node		*arg;
	long long	num;

	arg = final->tokens->next;
	if (!arg)
	{
		printf("exit\n");
		c_malloc(0, 0);
		exit(exit_status(0, 0));
	}
	if (!is_valid_number(arg->content))
		exit_help(arg);
	num = ft_atoi(arg->content);
	if ((num == 0 || num == -1) && arg->content[0] != '0'
		&& ft_strlen(arg->content) >= 19)
		exit_help(arg);
	if (arg->next)
		return (exit_helper());
	printf("exit\n");
	num = (num % 256 + 256) % 256;
	exit_status(1, num);
	c_malloc(0, 0);
	exit (num);
}
