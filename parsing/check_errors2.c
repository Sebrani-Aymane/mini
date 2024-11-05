/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:32:20 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/02 12:52:27 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirec_loop(char *input, int i, int inside_q, int q_type)
{
	while (input && input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			quotes_handle(input, &inside_q, &q_type, i);
		else if (!inside_q && is_redirection_op(input[i]))
		{
			i++;
			while (input[i] == ' ' || input[i] == '\t')
				i++;
			if (!print_error_message(i, input))
				return (0);
			while (input[i] && (input[i] == ' ' || input[i] == '\t')
				&& !is_redirection_op(input[i]))
				i++;
			continue ;
		}
		i++;
	}
	return (1);
}

int	validate_redirection_syntax(char *input)
{
	if (!handle_redirec_edge_cases(input))
		return (0);
	return (redirec_loop(input, 0, 0, 0));
}

int	handle_pipe_start_case(char *input, int i)
{
	if (input && input[i] == '|')
	{
		if (input[i + 1] && input[i + 1] == '|')
			printf("minishell: syntax error near unexpected token `||'\n");
		else
			printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

int	pipe_syntax(char *input, int i, int in_quotes)
{
	while (input && input[i] == ' ')
		i++;
	if (!handle_pipe_start_case(input, i))
		return (0);
	while (input && input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			in_quotes = !in_quotes;
		if (input[i] == '|' && !in_quotes)
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '\0' || input[i] == '|')
			{
				if (input[i + 1] && input[i + 1] == '|')
					printf("minshell:syntax error near unexpected token`|'\n");
				else
					printf("minishell:syntax error near unexpected token`|'\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_for_and(char *input)
{
	int	i;

	i = 0;
	if (input && input[0] == '&' && input[1] && input[1] == '&')
	{
		printf("minishell: syntax error near unexpected token `&&'\n");
		return (1);
	}
	while (input && input[i] && input[i + 1] && input[i + 2])
	{
		if (input[i] == '&' && input[i + 1] == '&' && input[i + 2] == '&')
		{
			printf("minishell: syntax error near unexpected token `&&'\n");
			return (1);
		}
		i++;
	}
	return (0);
}
