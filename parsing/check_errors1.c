/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:19:02 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/30 20:32:15 by cbajji           ###   ########.fr       */
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
		perror("minishell: unclosed quotes\n");
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
			perror("prohibited character\n");
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
		perror("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	if (input[0] == '&' && !input[1])
	{
		perror("minishell: syntax error near unexpected token `&'\n");
		return (0);
	}
	if (input[0] == '&' && input[1] && input[1] == '&')
	{
		perror("minishell: syntax error near unexpected token `&&'\n");
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
			perror("minishell: syntax error near unexpected token `|'\n");
		if (input[i] == '\0' || (input[0] == '!' && !input[1]))
			perror("minishell: syntax error near unexpected token `newline'\n");
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
