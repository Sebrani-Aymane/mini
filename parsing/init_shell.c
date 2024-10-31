/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:10:58 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/31 21:39:24 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	parse(char *input_rl, t_list *shell, env_vars *list_env)
{
	char	*input;

	input = malloc(sizeof(char) * ((pass_spaces_end(input_rl)
					- pass_spaces(input_rl)) + 2));
	copy_without_spaces(input, input_rl);
	if (!input || check_input(input))
	{
		free(input);
		free(input_rl);
		return (0);
	}
	shell->tokens = into_tokens(input, 0, 0);
	free(input);
	check_token_dollar(shell->tokens);
	expand(shell->tokens, list_env);
	expand_home(shell->tokens, list_env);
	return (1);
}

int	execution(char **env, env_vars *list_env, t_list *shell,
			struct termios *stats)
{
	t_node	*list;
	t_line	*lines;

	list = search_token(shell->tokens);
	check_for_delimeter(list);
	lines = tokens_to_lines(list);
	last_command(list_env, lines, ft_listsize(lines), lines->tokens);
	handle_heredoc(lines, list_env, stats);
	if (glob_var == 100)
		return (0);
	handle_pipe(lines, env, list_env);
	if (lines->fd_in)
		close(lines->fd_in);
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
			continue;
		}
		glob_var = 0;
		if (!parse(input_rl, &shell, list_env))
			continue ;
		if (!execution(env, list_env, &shell, &stats))
			continue ;
		free(input_rl);
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &stats) < 0)
			perror("terminal error ");
	}
}
