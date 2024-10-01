/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:59:21 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/01 14:53:04 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(char **envp,char *str)
{
	char	*path;
	int i = 0;
	
	if (!envp || !(*envp))
		return(NULL);
	while (envp[i])
	{	
		if (strncmp(envp[i], str,5) == 0)
			return(path  = ft_strdup(envp[i] + 5));
			i++;
	}
	return (NULL);
}

int	count_words(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			count++;
		while (*str && *str != c)
			str++;
	}
	return (count);
}

char	*return_word(char *str, char c)
{
	char	*ret;
	size_t		count;
	size_t		i;

	i = 0;
	count = 0;
	if (!str)
		return (NULL);
	while (str[count] != c && str[count] != '\0')
		count++;
	ret = c_malloc((count + 2), 1);
	if (!ret)
		return (NULL);
	while (i < count)
		ret[i++] = *(str++);
	ret[i] = '\0';
	return (ret);
}

void	clear_strss(char **strs, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(strs[i++]);
	free(strs);
}

int	ft_atoii(char *value)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*value)
	{
		while((*value <=13 && *value >= 9) || *value ==32)
			value++;
		break;
	}
	if (*value == '-')
	{
		sign = -1;
		value++;
	}
	else if (*value == '+')
		value++;
	while (*value)
	{
		result *= 10;
		result += (*value - '0');
		value++;
	}
	return (result * sign);
}
