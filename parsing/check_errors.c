/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:19:02 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/26 00:23:32 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_unclosed_quotes(char *input, int i, int inside_d, int inside_s)
{
	while (input && input[i])
	{
		if (input[i] == '"' && !inside_s)
			inside_d = !inside_d;
		else if (input[i] == '\'' && !inside_d)
			inside_s = !inside_s;
		i++;
	}
	if (inside_d || inside_s)
	{
		printf("minishell: unclosed quotes\n");
		return (1);
	}
	return (0);
}

int	check_prohibited_char(char *input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '\\' || input[i] == ';')
		{
			printf("prohibited character\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	handle_redirec_edge_cases(char *input)
{
	if (!input[0])
		return (0);
	if (more_than_op(input))
	{
		printf("minishell: syntax error near unexpected token `%c%c'\n",
			input[more_than_op(input) - 1], input[more_than_op(input)]);
		return (0);
	}
	if (input[0] == '!' && !input[1])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	if (input[0] == '&' && !input[1])
	{
		printf("minishell: syntax error near unexpected token `&'\n");
		return (0);
	}
	if (input[0] == '&' && input[1] && input[1] == '&')
	{
		printf("minishell: syntax error near unexpected token `&&'\n");
		return (0);
	}
	return (1);
}

int	print_error_message(int i, char *input)
{
	if (input[i] == '\0' || (is_redirection_op(input[i]) && input[i - 1] == ' ')
		|| input[i] == '|')
	{
		if (input[i] == '|')
			printf("minishell: syntax error near unexpected token `|'\n");
		if (input[i] == '\0' || (input[0] == '!' && !input[1]))
			printf("minishell: syntax error near unexpected token `newline'\n");
		if ((is_redirection_op(input[i]) && input[i - 1] == ' '))
		{
			if (input[i + 1] && is_redirection_op(input[i + 1]))
				printf("minishell: syntax error near unexpected token `%c%c'\n",
					input[i], input[i + 1]);
			else
				printf("minishell: syntax error near unexpected token `%c'\n",
					input[i]);
		}
		return (0);
	}
	return (1);
}

void	quotes_handle(char *input, int *inside_q, int *q_type, int i)
{
	if (*inside_q && input[i] == *q_type)
		*inside_q = 0;
	else if (*inside_q == 0)
	{
		*inside_q = 1;
		*q_type = input[i];
	}
	else
		return ;
}

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
