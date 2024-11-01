/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:39:33 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/01 21:37:19 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_env(char **env)
{
	int		size;
	char	**to_copy;
	int		i;

	i = 0;
	size = 0;
	while (env && env[size])
		size++;
	to_copy = c_malloc ((sizeof(char *) * (size + 1)), 1);
	if (!to_copy)
	{
		c_malloc(0, 0);
		exit(1);
	}
	while (env[i])
	{
		to_copy[i] = ft_strdup(env[i]);
		i++;
	}
	to_copy[i] = NULL;
	return (to_copy);
}

void	check_quotes(char *input, int *inside_d, int *inside_s, int i)
{
	if (input[i] == '"' && (*inside_s) == 0)
		(*inside_d) = !(*inside_d);
	else if (input[i] == '\'' && *inside_d == 0)
		(*inside_s) = !(*inside_s);
}

int	check_input(char *input)
{
	if (ft_is_space(input) || (input[0] == ':'
			&& !input[1]) || check_for_and(input))
		return (1);
	if (!ft_strcmp(input, "''") || !ft_strcmp(input, "\"\"")
		|| check_unclosed_quotes(input, 0, 0, 0)
		|| check_prohibited_char(input)
		|| !validate_redirection_syntax(input)
		|| !pipe_syntax(input, 0, 0))
	{
		if (!ft_strcmp(input, "\"\"") || !ft_strcmp(input, "''"))
			write(2, "minishell: : command not found\n", 31);
		exit_status(1, 127);
		return (1);
	}
	if (ft_strlenn(input) == 1 && input[0] != '/')
	{
		printf("minishell: %c:command not found\n", input[0]);
		exit_status(1, 127);
		return (1);
	}
	return (0);
}

char	*pass_dollar(char *content)
{
	int		i;
	char	*new;

	new = c_malloc(ft_strlen(content), 1);
	i = 1;
	while (content && content[i])
	{
		new[i - 1] = content[i];
		i++;
	}
	new[i - 1] = '\0';
	return (new);
}
