/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:39:33 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/30 21:48:38 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (!strcmp(input, "''") || !strcmp(input, "\"\"")
		|| check_unclosed_quotes(input, 0, 0, 0)
		|| check_prohibited_char(input)
		|| !validate_redirection_syntax(input)
		|| !pipe_syntax(input, 0, 0))
	{
		if (!strcmp(input, "\"\"") || !strcmp(input, "''"))
			perror("minishell: : command not found\n");
		exit_status(1, 127);
	}
	if (ft_strlenn(input) == 1 && input[0] != '/')
	{
		printf("minishell: %c:command not found\n", input[0]);
		exit_status(1, 127);
		return (1);
	}
	return (0);
}