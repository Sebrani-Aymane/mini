/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:10:58 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/30 21:49:17 by cbajji           ###   ########.fr       */
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

int	get_shlvl(char **env, int notif, int i)
{
	int		shlvl;
	char	*temp;

	temp = NULL;
	while (env && env[i])
	{
		if (!strncmp(env[i], "SHLVL", 5))
		{
			temp = env[i];
			notif = 1;
			break ;
		}
		i++;
	}
	if (notif)
	{
		while (temp && *temp != '=')
			temp++;
		temp++;
		shlvl = ft_atoi(temp) + 1;
		return (shlvl);
	}
	return (-1);
}

void	set_shlvl(t_list shell)
{
	char	*final;
	char	*nbr;
	int		i;

	i = 0;
	if (shell.shlvl != -1)
	{
		nbr = ft_itoa(shell.shlvl);
		final = ft_strjoin("SHLVL=", nbr);
		while (shell.env[i])
		{
			if (!strncmp(shell.env[i], "SHLVL", 5))
				shell.env[i] = final;
			i++;
		}
	}
}

int	super_function(char *input_rl, t_list shell, char **env, env_vars *list_env)
{
	t_node	*list;
	t_line	*lines;
	char	*input;

	input = malloc(sizeof(char) * ((ft_strlenn(input_rl)
					- pass_spaces(input_rl)) + 2));
	copy_without_spaces(input, input_rl);
	if (check_input(input))
	{
		free(input);
		free(input_rl);
		return (0);
	}
	shell.tokens = into_tokens(input, 0, 0);
	free(input);
	check_token_dollar(shell.tokens);
	expand(shell.tokens, list_env);
	expand_home(shell.tokens, list_env);
	list = search_token(shell.tokens);
	check_for_delimeter(list);
	lines = tokens_to_lines(list);
	last_command(list_env, lines, ft_listsize(lines), lines->tokens);
	handle_heredoc(lines, list_env);
	handle_pipe(lines, env, list_env);
	return (1);
}

void	display_prompt(t_list shell, char **env, env_vars *list_env)
{
	char			*input_rl;
	struct termios	stats;

	if (tcgetattr(STDIN_FILENO, &stats) < 0)
		perror("terminal error ");
	while (1)
	{
		input_rl = readline("minishell-1.0$ ");
		if (glob_var)
			exit_status(1, 1);
		sig_handler(input_rl);
		if (strcmp(input_rl, ""))
			add_history(input_rl);
		if (ft_is_space(input_rl))
		{
			free(input_rl);
			continue ;
		}
		glob_var = 0;
		if (!super_function(input_rl, shell, env, list_env))
			continue ;
		free(input_rl);
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &stats) < 0)
			perror("terminal error ");
	}
}
