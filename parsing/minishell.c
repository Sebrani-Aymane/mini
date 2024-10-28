/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:14:20 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/28 06:25:53 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	sigint_handler(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	glob_var = SIGINT;
}
void sigint_hand_heredoc(int signal)
{
	(void)signal;
	printf("\n");
	glob_var = SIGINT;
	exit(1);
}

void	handle_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_list		shell;
	env_vars	*list_env;
	(void)av;
	(void)ac;

	if (!*env)
		env = fake_env();
	shell.env = copy_env(env);
	list_env = list_init(shell.env);
	shell.shlvl = get_shlvl(shell.env);
	set_shlvl(shell);
	handle_signals();
	display_prompt(shell, shell.env, list_env);
	c_malloc(0, 0);
}
